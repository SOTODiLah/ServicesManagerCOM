// FactoryServiceManager.cpp: реализация CFactoryServiceManager

#include "pch.h"
#include "FactoryServiceManager.h"


// CFactoryServiceManager
STDMETHODIMP CFactoryServiceManager::GetAllServiceManagers(SAFEARRAY** pResult)
{
	if (!pResult)
		return E_POINTER;

	std::queue<BSTR> qServices;
	HRESULT hr = SelectServices(qServices);
	if (FAILED(hr))
		return hr;

	hr = CreateArray(qServices, pResult);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

STDMETHODIMP CFactoryServiceManager::GetServiceManagersByType(EServiceType eType, SAFEARRAY** pResult)
{
	if (!pResult)
		return E_POINTER;

	std::queue<BSTR> qServices;
	std::function<bool(LPENUM_SERVICE_STATUS_PROCESS)> fSelect = [need = (DWORD)eType](LPENUM_SERVICE_STATUS_PROCESS essp) -> bool
	{
		return essp->ServiceStatusProcess.dwServiceType == need;
	};

	HRESULT hr = SelectServices(qServices, fSelect);
	if (FAILED(hr))
		return hr;

	hr = CreateArray(qServices, pResult);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

STDMETHODIMP CFactoryServiceManager::GetServiceManagersByStatus(EServiceStatus eStatus, SAFEARRAY** pResult)
{
	if (!pResult)
		return E_POINTER;

	std::queue<BSTR> qServices;
	std::function<bool(LPENUM_SERVICE_STATUS_PROCESS)> fSelect = [need = (DWORD)eStatus](LPENUM_SERVICE_STATUS_PROCESS essp) -> bool
	{
		return essp->ServiceStatusProcess.dwCurrentState == need;
	};

	HRESULT hr = SelectServices(qServices, fSelect);
	if (FAILED(hr))
		return hr;

	hr = CreateArray(qServices, pResult);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT CFactoryServiceManager::SelectServices(std::queue<BSTR>& qServices, std::function<bool(LPENUM_SERVICE_STATUS_PROCESS)> fSelect)
{
	CServiceHandle scHandle = ::OpenSCManager(nullptr, nullptr, SC_MANAGER_ENUMERATE_SERVICE);

	if (!scHandle)
		return E_FAIL;

	DWORD dwBytesNeeded{ 0 };
	DWORD dwServicesReturnedCount{ 0 };
	DWORD dwResumeHandle{ 0 };

	do
	{
		if (!EnumServicesStatusEx(scHandle, SC_ENUM_PROCESS_INFO, SERVICE_TYPE_ALL, SERVICE_STATE_ALL,
			nullptr, 0, &dwBytesNeeded, &dwServicesReturnedCount, &dwResumeHandle, nullptr))
		{
			if (ERROR_MORE_DATA == ::GetLastError())
			{
				std::vector<unsigned char> buffer(dwBytesNeeded, 0);

				if (EnumServicesStatusEx(scHandle, SC_ENUM_PROCESS_INFO, SERVICE_TYPE_ALL, SERVICE_STATE_ALL,
					reinterpret_cast<LPBYTE>(buffer.data()), dwBytesNeeded, &dwBytesNeeded, &dwServicesReturnedCount, nullptr, nullptr))
				{
					auto essp = reinterpret_cast<LPENUM_SERVICE_STATUS_PROCESS>(buffer.data());

					if (!essp)
						return E_FAIL;

					for (auto i = DWORD{ 0 }; i < dwServicesReturnedCount; ++i)
					{
						if (fSelect != nullptr)
							if (!fSelect(essp))
								continue;
						qServices.push(SysAllocString(essp->lpServiceName));
					}
				}
				else break;
			}
			else break;
		}
	} while (dwResumeHandle != 0);

	return S_OK;
}

HRESULT CFactoryServiceManager::CreateArray(std::queue<BSTR>& qServices, SAFEARRAY** pResult)
{
	if (!pResult)
		return E_POINTER;
	
	if (qServices.empty())
		return S_OK;

	
	size_t lLbound = 0;
	size_t cElements = qServices.size();
	SAFEARRAY* psa = SafeArrayCreateVector(VT_DISPATCH, (ULONG)lLbound, (ULONG)cElements);

	if (!psa)
		return E_FAIL;

	HRESULT hr;
	CComPtr<IServiceManager> ptrContent;
	for (LONG i = 0; i < cElements; i++)
	{
		hr = ptrContent.CoCreateInstance(CLSID_ServiceManager);
		if (FAILED(hr))
			break;

		hr = ptrContent->Init(qServices.front());
		if (FAILED(hr))
			break;
		qServices.pop();

		hr = SafeArrayPutElement(psa, &i, ptrContent.Detach());
		if (FAILED(hr))
			break;
	}

	if (FAILED(hr))
	{
		SafeArrayDestroy(psa);
		return hr;
	}

	*pResult = psa;
	return S_OK;
}