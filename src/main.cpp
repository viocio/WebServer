#include <iostream>
#include "server.hpp"
#include "parser.hpp"

int main()
{
    int port, conexiuniMaxime;
    std::cout << "Portul pe care vrei sa deschizi serverul: ";
    std::cin >> port;
    std::cout << "Cate conexiuni vrei sa accepte serverul? ";
    std::cin >> conexiuniMaxime;
    viorel::Server serverHTTP(port, conexiuniMaxime);
    serverHTTP.namingTheSocket();
    serverHTTP.setSocketForListening();
    while (1)
    {
        int socketClient = serverHTTP.acceptingConnections();
        char buffer[2048];
        recv(socketClient, buffer, sizeof(buffer), 0);
        std::string requestString(buffer);
        HTTPresponse response = httpHandler(requestString);
    }
}