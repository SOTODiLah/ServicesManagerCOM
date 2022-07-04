# ServicesManagerCOM
C++ COM working with services and project C# Forms using this COM

## Project ServicesManagerCOM

Проект ATL. Содержит два COM-object имеют двойной интерфейс, что позволяет использовать ранее и позднее связывание.

* СServiceManager
* CFactoryServiceManagers 

Файл .idl описывает языком интерфейсов (MIDL) структуры классов и перечислений использующихся в COM-object.

## Project Form_COM

Проект Windows Forms C#. Реализован базовый UI для демонстрации работы COM-object. Используется ранее связывание, пример описание интерфейсов в "Forms_COM/Forms_COM/InterfaceCOM.cs"


## Launch

Запуск программы осуществляет через командную строку.<br>
```bash
Options:
  -h,--help                   Вывод этого справочного сообщения.
  -i,--input TEXT             Путь до входного файла.
  -o,--output TEXT            Путь до выходного файла.
  -s,--sizeBuffer UINT        Размер буфера (блока файла).
````
