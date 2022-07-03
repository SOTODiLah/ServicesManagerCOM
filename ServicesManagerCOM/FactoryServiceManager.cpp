// FactoryServiceManager.cpp: реализация CFactoryServiceManager

#include "pch.h"
#include "FactoryServiceManager.h"


// CFactoryServiceManager
STDMETHODIMP CFactoryServiceManager::GetAllServiceManagers(SAFEARRAY**)
{
	return S_OK;
}

STDMETHODIMP CFactoryServiceManager::GetServiceManagersByType(SAFEARRAY**)
{
	return S_OK;
}

STDMETHODIMP CFactoryServiceManager::GetServiceManagersByState(SAFEARRAY**)
{
	return S_OK;
}
