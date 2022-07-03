// ServicesManager.cpp: реализация CServicesManager

#include "pch.h"
#include "ServiceManager.h"

// CServicesManager
STDMETHODIMP CServiceManager::Init(BSTR bstrName)
{
	if (!bstrName)
		return E_POINTER;

	m_wstrName = bstrName;

	if (m_wstrName.empty())
		return E_FAIL;

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

STDMETHODIMP CServiceManager::GetName(BSTR* pResult) 
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = SysAllocString(m_wstrName.c_str());
	return hr;
}

STDMETHODIMP CServiceManager::GetFullName(BSTR* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = SysAllocString(m_wstrFullName.c_str());
	return hr;
}

STDMETHODIMP CServiceManager::GetDescription(BSTR* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = SysAllocString(m_wstrDescription.c_str());
	return hr;
}

STDMETHODIMP CServiceManager::GetStatus(EServiceStatus* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = m_eStatus;
	return hr;
}

STDMETHODIMP CServiceManager::GetType(EServiceType* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = m_eType;
	return hr;
}

STDMETHODIMP CServiceManager::CanPauseContinue(boolean* pResult)
{
	HRESULT hr = CheckInit((void**)pResult);
	*pResult = m_bPauseContinue;
	return hr;
}

STDMETHODIMP CServiceManager::CanStop(boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = m_bStop;
	return hr;
}

STDMETHODIMP CServiceManager::Start(boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);

	return hr;
}

STDMETHODIMP CServiceManager::Stop(boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	return hr;
}

STDMETHODIMP CServiceManager::Pause(boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	return hr;
}

STDMETHODIMP CServiceManager::Continue(boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	return hr;
}

STDMETHODIMP CServiceManager::Restart(boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	return hr;
}

STDMETHODIMP CServiceManager::WaitForStatus(EServiceStatus eStatus, ULONG ulTime, boolean* pResult)
{
	HRESULT hr = CheckInit((void*)pResult);
	*pResult = 0;
	if (FAILED(hr))
		return hr;

	hr = UpdateStatus();
	if (FAILED(hr))
		return hr;

	auto startTime = std::chrono::high_resolution_clock::now();
	auto waitTime = GetWaitTime(m_dwWaitHint);
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

STDMETHODIMP CServiceManager::Refresh()
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

HRESULT CServiceManager::UpdateStatus()
{
	if (!m_scHandle)
		return E_FAIL;
	if (m_wstrName.empty())
		return E_FAIL;

	CServiceHandle srvHandle = ::OpenService(m_scHandle, m_wstrName.c_str(), SERVICE_QUERY_STATUS);

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
	if (!m_scHandle)
		return E_FAIL;
	if (m_wstrName.empty())
		return E_FAIL;

	CServiceHandle srvHandle = ::OpenService(m_scHandle, m_wstrName.c_str(), SERVICE_QUERY_CONFIG);

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
	if (!m_scHandle)
		return E_FAIL;
	if (m_wstrName.empty())
		return E_FAIL;

	CServiceHandle srvHandle = ::OpenService(m_scHandle, m_wstrName.c_str(), SERVICE_QUERY_CONFIG);

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

HRESULT CServiceManager::CheckInit(void* ptr)
{
	if (!ptr)
		return E_POINTER;
	if (!m_bInit)
		return E_UNEXPECTED;
	return S_OK;
}

std::chrono::milliseconds CServiceManager::GetWaitTime(DWORD const waitHint)
{
	auto waitTime = waitHint / 10;

	if (waitTime < 1000)
		waitTime = 1000;
	else if (waitTime > 10000)
		waitTime = 10000;

	return std::chrono::milliseconds(waitTime);
}