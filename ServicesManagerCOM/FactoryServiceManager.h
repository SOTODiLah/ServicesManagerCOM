// FactoryServiceManager.h: объявление CFactoryServiceManager

#pragma once
#include "resource.h"       // основные символы



#include "ServicesManagerCOM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;

#include "ServiceHandle.h"
#include <vector>
#include <queue>
#include <functional>

// CFactoryServiceManager

class CFactoryServiceManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFactoryServiceManager, &CLSID_FactoryServiceManager>,
	public IDispatchImpl<IFactoryServiceManager, &IID_IFactoryServiceManager, &LIBID_ServicesManagerCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFactoryServiceManager()
	{
	}

DECLARE_REGISTRY_RESOURCEID(107)


BEGIN_COM_MAP(CFactoryServiceManager)
	COM_INTERFACE_ENTRY(IFactoryServiceManager)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(GetAllServiceManagers(SAFEARRAY**));
	STDMETHOD(GetServiceManagersByType(EServiceType, SAFEARRAY**));
	STDMETHOD(GetServiceManagersByStatus(EServiceStatus, SAFEARRAY**));

private:
	HRESULT SelectServices(std::queue<BSTR>&, std::function<bool(LPENUM_SERVICE_STATUS_PROCESS)> = nullptr);
	HRESULT CreateArray(std::queue<BSTR>&, SAFEARRAY**);

};

OBJECT_ENTRY_AUTO(__uuidof(FactoryServiceManager), CFactoryServiceManager)
