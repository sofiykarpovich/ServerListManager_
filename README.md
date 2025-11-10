# ServerListManager

Простой проект на **C++17** для управления списком IP-адресов серверов, хранящихся в `.txt` файле.  
Реализованы функции для:
- чтения списка серверов (`GetServersList`)
- добавления нового сервера (`AddServer`)
- удаления сервера (`DeleteServer`)

**Как собрать**

_Создать папку сборки_

mkdir build
cd build

_Настроить CMake_

cmake ..

_Собрать проект_

cmake --build .

**Как запустить тесты**

cd build
ctest --verbose

# Пример использования

#include "ServerManager.h"

ServerManager manager("servers.txt");

manager.AddServer("192.168.1.1");

manager.AddServer("10.0.0.5");

auto servers = manager.GetServersList();

for (const auto& ip : servers) {

    std::cout << ip << std::endl;
    
}

manager.DeleteServer("192.168.1.1");

**Пример содержимого servers.txt**

192.168.1.1
10.0.0.5
203.0.113.10

**Пример использования  servers.txt.log**

ADD 192.168.1.1
ADD 10.0.0.5
DEL 192.168.1.1

**Требования**

- Компилятор: C++17 совместимый (GCC 7+, Clang 5+)

- CMake: версия 3.14 или выше

- Библиотеки: GoogleTest (автоматически загружается)
