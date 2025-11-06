#include <iostream>
#include "server.hpp"

int main()
{
    int port, conexiuniMaxime;
    std::cout << "Portul pe care vrei sa deschizi serverul: ";
    std::cin >> port;
    std::cout << "Cate conexiuni vrei sa accepte serverul? ";
    std::cin >> conexiuniMaxime;
    server::ServerHTTP serverHTTP(port, conexiuniMaxime);
    serverHTTP.namingTheSocket();
    serverHTTP.setSocketForListening();
    while (1)
    {
        serverHTTP.acceptingConnections();
    }
}