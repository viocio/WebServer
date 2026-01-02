#include <iostream>
#include "server.hpp"
#include "parser.hpp"

int main()
{
    int port, conexiuniMaxime;
    int numarSecundeTimeout = 5;
    std::string pathRelativ;
    std::cout << "Portul pe care vrei sa deschizi serverul: ";
    std::cin >> port;
    std::cout << "Cate conexiuni vrei sa accepte serverul? ";
    std::cin >> conexiuniMaxime;
    std::cout << "Pune / dupa path: Ex: ~/site/";
    std::cout << "Path relativ pentru site: ";
    std::cin >> pathRelativ;
    viorel::Server serverHTTP(port, conexiuniMaxime);
    serverHTTP.namingTheSocket();
    serverHTTP.setSocketForListening();
    while (true)
    {
        int socketClient = serverHTTP.acceptingConnections();
        timeval tv;
        tv.tv_sec = numarSecundeTimeout;
        tv.tv_usec = 0;
        setsockopt(socketClient, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        while (true)
        {
            std::string requestString = serverHTTP.receivingRequest(socketClient); // recv() will be called in this function

            std::string response = httpHandler(requestString, pathRelativ);
            serverHTTP.sendData(response, socketClient);
        }
    }
    return 0;
}