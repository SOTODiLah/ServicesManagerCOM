# ServicesManagerCOM
C++ COM working with services and project C# Forms using this COM

## Project ServicesManagerCOM ([README](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/README.md))

Проект ATL. Содержит два COM-object имеют двойной интерфейс, что позволяет использовать ранее и позднее связывание.

* ServiceManager
* FactoryServiceManagers 

Файл [ServicesManagerCOM.idl](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/ServicesManagerCOM/ServicesManagerCOM.idl) описывает языком интерфейсов (MIDL) структуры классов и перечислений использующихся в COM-object.

## Project Form_COM ([README](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/Forms_COM/Forms_COM/README.md))

Проект Windows Forms C#. Реализован базовый UI для демонстрации работы COM-object.<br>
Используется ранее связывание. Описание интерфейсов в C# [InterfaceCOM.cs](https://github.com/SOTODiLah/ServicesManagerCOM/blob/master/Forms_COM/Forms_COM/InterfaceCOM.cs)

## Использование COM DLL

Регистрация DLL осуществляется через командную строку или созданием файла *.reg*.<br>
При регистрации DLL x86 в операционных система x64 используйте специальные пути.

### Региструем в реестре
```bash
regsvr32 /i ServicesManagerCOM.dll
````
### Отменяем регистрацию
```bash
regsvr32 /u ServicesManagerCOM.dll
````
