// dllmain.h: объявление класса модуля.

class CServicesManagerCOMModule : public ATL::CAtlDllModuleT< CServicesManagerCOMModule >
{
public :
	DECLARE_LIBID(LIBID_ServicesManagerCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SERVICESMANAGERCOM, "{a871ac02-f7c1-4a9e-b060-95645d1d5826}")
};

extern class CServicesManagerCOMModule _AtlModule;
