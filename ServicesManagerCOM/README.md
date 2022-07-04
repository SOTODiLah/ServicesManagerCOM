# Project ServicesManagerCOM

Большинство файлов генерирует Visual Studio. При написании COM-object'ов самостоятельно, много времени уходит на описание интерфейсов и реализацию функции DLL (если вы создаёте внутрипотоковый COM, а не .EXE).

## Файлы проекта

* [ServicesManagerCOM.idl](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/ServicesManagerCOM.idl) - описание интерфейсов COM-object'ов.
* [ServiceHandle.h](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/ServiceHandle.h) - вспомогательный класс закрывающий через деструктор обращение к SC_HANDLE.
* [ServiceManager.h](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/ServiceManager.h)/[ServiceManager.cpp](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/ServiceManager.cpp) - класс реализации менеджера службы. COM-object работающий с конкретной службой Windows.
* [FactoryServiceManager.h](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/FactoryServiceManager.h)/[FactoryServiceManager.cpp](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/FactoryServiceManager.cpp) - класс реализации фабрики менеджеров служб. COM-object создающий массив отобранных служб.
