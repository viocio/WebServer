#include "server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <iostream>
#include <cstring>

void server::ServerHTTP::writeSocketAddress(sockaddr_in &serveradd, int port_)
{
    serveradd.sin_family = AF_INET;
    inet_pton(AF_INET, "172.16.1.96", &serveradd.sin_addr.s_addr);
    serveradd.sin_port = htons(port_);
}

server::ServerHTTP::ServerHTTP(int port_)
{
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) // inlocuieste 0 cu IP_PROTOTCP
    {
        throw std::runtime_error("Eroare la crearea socketului!\n");
        std::cout << strerror(errno) << " " << "Cod eroare: " << errno;
    }
    else
    {
        std::cout << "Socket creat cu succes!" << "\n";
        std::cout << sock << "\n";
        // afiseaza numarul socketului
    }
    writeSocketAddress(serveradd, port_);
    if (bind(sock, (sockaddr *)&serveradd, sizeof(serveradd)) < 0)
    {
        throw std::runtime_error("Eroare la bind! \n");
        std::cout << strerror(errno) << " " << "Cod eroare: " << errno;
    }
    else
    {
        std::cout << "Succes la bind!\n";
    }
}

server::ServerHTTP::~ServerHTTP()
{
}