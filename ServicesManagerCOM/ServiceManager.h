// ServicesManager.h: объявление CServicesManager

#pragma once
#include "resource.h"       // основные символы



#include "ServicesManagerCOM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;

#include "ServiceHandle.h"
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#ifdef UNICODE
#define ServiceString std::wstring
#else
#define ServiceString std::string
#endif

// CServicesManager
class CServiceManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CServiceManager, &CLSID_ServiceManager>,
	public IDispatchImpl<IServiceManager, &IID_IServiceManager, &LIBID_ServicesManagerCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CServiceManager()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CServiceManager)
	COM_INTERFACE_ENTRY(IServiceManager)
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
	 STDMETHOD(InitService(BSTR));
	 STDMETHOD(GetServiceName(BSTR*));
	 STDMETHOD(GetServiceFullName(BSTR*));
	 STDMETHOD(GetServiceDescription(BSTR*));
	 STDMETHOD(GetServiceStatus(EServiceStatus*));
	 STDMETHOD(GetServiceType(EServiceType*));
	 STDMETHOD(CanServicePauseContinue(boolean*));
	 STDMETHOD(CanServiceStop(boolean*));
	 STDMETHOD(WaitForServiceStatus(EServiceStatus, ULONG, boolean*));
	 STDMETHOD(ServiceRefresh());
	 STDMETHOD(ServiceStart(boolean*));
	 STDMETHOD(ServiceStop(boolean*));
	 STDMETHOD(ServicePause(boolean*));
	 STDMETHOD(ServiceContinue(boolean*));
private:
	HRESULT ChangeStatus(DWORD const, DWORD const , boolean*);
	HRESULT UpdateStatus();
	HRESULT UpdateConfig();
	HRESULT UpdateAdditionalConfig();
	std::chrono::milliseconds GetWaitTime();
	inline HRESULT CheckInit(void* ptr) const;
	inline SC_HANDLE OpenHandle(DWORD const) const;
	inline void IsAppRunningAsAdminMode();

private:
	bool m_bInit{ false };
	BOOL m_bRunAsAdmin{ FALSE };
	ServiceString m_wstrName{ L"" };
	ServiceString m_wstrFullName{ L"" };
	ServiceString m_wstrDescription{ L"" };
	EServiceStatus m_eStatus{ EServiceStatus::NonStatus };
	EServiceType m_eType{ EServiceType::NonType };
	boolean m_bPauseContinue{ 0 };
	boolean m_bStop{ 0 };
	DWORD m_dwWaitHint{ 0 };
	CServiceHandle m_scHandle{ nullptr };
};

OBJECT_ENTRY_AUTO(__uuidof(ServiceManager), CServiceManager)
