#include <iostream>
#include "server.hpp"
#include "parser.hpp"
#include <unistd.h>
#include <thread>

void handleClient(viorel::Server &serverHTTP, int socketClient, const std::string &badPOST, const std::string &pathRelativ)
{
    std::string pending;
    while (true)
    {
        bool postIncomplet = false;
        std::string requestString = serverHTTP.receivingRequest(socketClient, postIncomplet, pending); // recv() will be called in this function
        // functia recv() este blocking, deci in interiorul lui receivingRequest executia sa va opri fie
        // cand clientul inchide conexiunea si recv() intoarce 0, fie cand e timeout si recv() intoarce -1,
        // fie clientul primeste ceva si recv() intoarce numarul de octeti primiti
        // pentru -1 si 0 functia receivingRequest returneaza un empty string
        if (requestString.empty())
        {
            if (postIncomplet)
            {
                serverHTTP.sendData(badPOST, socketClient);
            }
            break;
        }
        else
        {
            std::string response = httpHandler(requestString, pathRelativ);
            serverHTTP.sendData(response, socketClient);
        }
    }
    close(socketClient);
}

int main()
{
    int port, conexiuniMaxime;
    int numarSecundeTimeout = 5;
    std::string badPOST =
        "HTTP/1.1 408 Request Timeout\r\n"
        "Connection: close\r\n"
        "Content-Length: 0\r\n"
        "\r\n";
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
        std::thread([&, socketClient]()
                    { handleClient(serverHTTP, socketClient, badPOST, pathRelativ); })
            .detach();
    }
    return 0;
}