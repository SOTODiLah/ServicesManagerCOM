// ServicesManager.cpp: реализация CServicesManager

#include "pch.h"
#include "ServiceManager.h"

// CServicesManager
STDMETHODIMP CServiceManager::InitService(BSTR bstrName)
{
	if (!bstrName)
		return E_POINTER;

	m_wstrName = bstrName;

	if (m_wstrName.empty())
		return E_FAIL;

	IsAppRunningAsAdminMode();

	m_scHandle = ::OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT);

	if (!m_scHandle)
		return E_ACCESSDENIED;

	HRESULT hr, hrReturn;
	hrReturn = S_OK;

	hr = UpdateStatus();
	if (FAILED(hr))
		return hr;
	if (hr == S_FALSE)
		hrReturn = hr;

	hr = UpdateConfig();
	if (FAILED(hr))
		return hr;
	if (hr == S_FALSE)
		hrReturn = hr;

	hr = UpdateAdditionalConfig();
	if (FAILED(hr))
		return hr;
	if (hr == S_FALSE)
		hrReturn = hr;
	
	m_bInit = true;

	return hrReturn;
}

STDMETHODIMP CServiceManager::GetServiceName(BSTR* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	if (SUCCEEDED(hr))
		*pResult = SysAllocString(m_wstrName.c_str());
	return S_OK;
}

STDMETHODIMP CServiceManager::GetServiceFullName(BSTR* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	if (SUCCEEDED(hr))
		*pResult = SysAllocString(m_wstrFullName.c_str());
	return S_OK;
}

STDMETHODIMP CServiceManager::GetServiceDescription(BSTR* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	if (SUCCEEDED(hr))
		*pResult = SysAllocString(m_wstrDescription.c_str());
	return hr;
}

STDMETHODIMP CServiceManager::GetServiceStatus(EServiceStatus* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	if (FAILED(hr))
		return hr;
	hr = UpdateStatus();
	if (FAILED(hr))
		return hr;
	*pResult = m_eStatus;
	return hr;
}

STDMETHODIMP CServiceManager::GetServiceType(EServiceType* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	if (SUCCEEDED(hr))
		*pResult = m_eType;
	return hr;
}

STDMETHODIMP CServiceManager::CanServicePauseContinue(boolean* pResult)
{
	HRESULT hr = CheckInit((void**)pResult);
	if (FAILED(hr))
		return hr;
	hr = UpdateStatus();
	if (FAILED(hr))
		return hr;
	*pResult = m_bPauseContinue;
	return hr;
}

STDMETHODIMP CServiceManager::CanServiceStop(boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	if (FAILED(hr))
		return hr;
	hr = UpdateStatus();
	if (FAILED(hr))
		return hr;
	*pResult = m_bStop;
	return hr;
}

STDMETHODIMP CServiceManager::ServiceStart(boolean* pResult)
{
	HRESULT hr = CheckInit(pResult);
	if (FAILED(hr))
		return hr;

	*pResult = 0;
	if (!m_bRunAsAdmin)
		return S_FALSE;
	
	CServiceHandle srvHandle = OpenHandle(SERVICE_START);

	if (!srvHandle)
		return E_FAIL;

	auto res = ::StartService(srvHandle, 0, nullptr);

	if (!res)
		return S_FALSE;

	hr = UpdateStatus();
	*pResult = 1;
	return S_OK;
}

STDMETHODIMP CServiceManager::ServiceStop(boolean* pResult)
{
	if (!m_bRunAsAdmin || !m_bStop)
		return S_FALSE;

	return ChangeStatus(SERVICE_STOP, SERVICE_CONTROL_STOP, pResult);
}

STDMETHODIMP CServiceManager::ServicePause(boolean* pResult)
{
	if (!m_bRunAsAdmin || !m_bPauseContinue)
		return S_FALSE;
	return ChangeStatus(SERVICE_PAUSE_CONTINUE, SERVICE_CONTROL_PAUSE, pResult);
}

STDMETHODIMP CServiceManager::ServiceContinue(boolean* pResult)
{
	if (!m_bRunAsAdmin || !m_bPauseContinue)
		return S_FALSE;
	return ChangeStatus(SERVICE_PAUSE_CONTINUE, SERVICE_CONTROL_CONTINUE, pResult);
}

STDMETHODIMP CServiceManager::WaitForServiceStatus(EServiceStatus eStatus, ULONG ulTime, boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = 0;
	if (FAILED(hr))
		return hr;

	hr = UpdateStatus();
	if (FAILED(hr))
		return hr;

	auto startTime = std::chrono::high_resolution_clock::now();
	auto waitTime = GetWaitTime();
	std::chrono::milliseconds timeout{ ulTime };

	while (eStatus != m_eStatus)
	{
		std::this_thread::sleep_for(waitTime);
		hr = UpdateStatus();
		if (FAILED(hr))
			return hr;
		if (std::chrono::high_resolution_clock::now() - startTime > timeout)
			break;
	}

	if (eStatus == m_eStatus)
		*pResult = 1;

	return S_OK;
}

STDMETHODIMP CServiceManager::ServiceRefresh()
{
	if (!m_bInit)
		return E_UNEXPECTED;
	HRESULT hr;

	hr = UpdateStatus();
	if (FAILED(hr))
		return hr;

	hr = UpdateConfig();
	if (FAILED(hr))
		return hr;

	hr = UpdateAdditionalConfig();
	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT CServiceManager::ChangeStatus(DWORD const dwDesiredAccess, DWORD const controlCode, boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	if (FAILED(hr))
		return hr;
	*pResult = 0;

	CServiceHandle srvHandle = OpenHandle(dwDesiredAccess);
	if (!srvHandle)
		return E_FAIL;

	SERVICE_STATUS_PROCESS ssp{ 0 };
	if (!::ControlService(srvHandle, controlCode, reinterpret_cast<LPSERVICE_STATUS>(&ssp)))
		return S_FALSE;

	m_eStatus = (EServiceStatus)ssp.dwCurrentState;
	m_bPauseContinue = ssp.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE;
	m_bStop = ssp.dwControlsAccepted & SERVICE_ACCEPT_STOP;
	m_dwWaitHint = ssp.dwWaitHint;

	*pResult = 1;
	return S_OK;
}

HRESULT CServiceManager::UpdateStatus()
{
	CServiceHandle srvHandle = OpenHandle(SERVICE_QUERY_STATUS);

	if (!srvHandle)
		return S_FALSE;

	auto dwBytesNeeded = DWORD{ 0 };
	auto ssp = SERVICE_STATUS_PROCESS{ 0 };

	auto bStatus = ::QueryServiceStatusEx(
		srvHandle,
		SC_STATUS_PROCESS_INFO,
		reinterpret_cast<LPBYTE>(&ssp),
		sizeof(ssp),
		&dwBytesNeeded);

	if (!bStatus)
		return S_FALSE;

	m_eStatus = (EServiceStatus)ssp.dwCurrentState;
	m_bPauseContinue = ssp.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE;
	m_bStop = ssp.dwControlsAccepted & SERVICE_ACCEPT_STOP;
	m_dwWaitHint = ssp.dwWaitHint;

	return S_OK;
}

HRESULT CServiceManager::UpdateConfig()
{
	CServiceHandle srvHandle = OpenHandle(SERVICE_QUERY_CONFIG);

	if (!srvHandle)
		return S_FALSE;

	auto dwBytesNeeded = DWORD{ 0 };

	if (QueryServiceConfig(srvHandle, nullptr, NULL, &dwBytesNeeded))
		return S_FALSE;
	if (ERROR_INSUFFICIENT_BUFFER != ::GetLastError())
		return S_FALSE;

	std::vector<unsigned char> vecBuffer(dwBytesNeeded, 0);
	auto lpsc = reinterpret_cast<LPQUERY_SERVICE_CONFIG>(vecBuffer.data());

	if (!QueryServiceConfig(srvHandle, lpsc, dwBytesNeeded, &dwBytesNeeded))
		return S_FALSE;

	if (!lpsc)
		return S_FALSE;

	if (lpsc->lpDisplayName)
		m_wstrFullName = lpsc->lpDisplayName;
	else
		m_wstrFullName = L"";

	m_eType = (EServiceType)lpsc->dwServiceType;

	return S_OK;
}

HRESULT CServiceManager::UpdateAdditionalConfig()
{
	CServiceHandle srvHandle = OpenHandle(SERVICE_QUERY_CONFIG);

	if (!srvHandle)
		return S_FALSE;

	auto dwBytesNeeded = DWORD{ 0 };

	if (QueryServiceConfig2(srvHandle, SERVICE_CONFIG_DESCRIPTION, nullptr, NULL, &dwBytesNeeded))
		return S_FALSE;
	if (ERROR_INSUFFICIENT_BUFFER != ::GetLastError())
		return S_FALSE;

	std::vector<unsigned char> vecBuffer(dwBytesNeeded, 0);

	if (!QueryServiceConfig2(srvHandle, SERVICE_CONFIG_DESCRIPTION, reinterpret_cast<LPBYTE>(vecBuffer.data()), dwBytesNeeded, &dwBytesNeeded))
		return S_FALSE;

	auto lpsc = reinterpret_cast<LPSERVICE_DESCRIPTION>(vecBuffer.data());

	if (!lpsc)
		return S_FALSE;

	if (lpsc->lpDescription)
		m_wstrDescription = lpsc->lpDescription;
	else
		m_wstrDescription = L"";

	return S_OK;
}

SC_HANDLE CServiceManager::OpenHandle(DWORD const dwDesiredAccess) const
{
	if (!m_scHandle || m_wstrName.empty())
		return nullptr;
	return ::OpenService(m_scHandle, m_wstrName.c_str(), dwDesiredAccess);
}

std::chrono::milliseconds CServiceManager::GetWaitTime()
{
	auto waitTime = m_dwWaitHint / 10;

	if (waitTime < 1000)
		waitTime = 1000;
	else if (waitTime > 10000)
		waitTime = 10000;

	return std::chrono::milliseconds(waitTime);
}

void CServiceManager::IsAppRunningAsAdminMode()
{
	m_bRunAsAdmin = FALSE;
	PSID pAdministratorsGroup = NULL;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;

	if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdministratorsGroup))
	{
		CheckTokenMembership(NULL, pAdministratorsGroup, &m_bRunAsAdmin);
	}

	if (pAdministratorsGroup)
	{
		FreeSid(pAdministratorsGroup);
		pAdministratorsGroup = NULL;
	}
}

HRESULT CServiceManager::CheckInit(void* ptr) const
{
	if (!ptr)
		return E_POINTER;
	if (!m_bInit)
		return E_UNEXPECTED;
	return S_OK;
}

