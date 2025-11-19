#include "server.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>

// Metode private

bool viorel::Server::noProblems(int var)
{
    bool succes;
    if (var < 0)
    {
        succes = false;
        throw std::runtime_error("Eroare!\n");
        std::cout << strerror(errno) << " " << "Cod eroare: " << errno;
        return succes;
    }
    else
    {
        succes = true;
        return succes;
    }
}

void viorel::Server::writeSocketAddress(sockaddr_in &vioreladd, int port_)
{
    vioreladd.sin_family = AF_INET;
    inet_pton(AF_INET, "172.16.1.96", &vioreladd.sin_addr.s_addr);
    vioreladd.sin_port = htons(port_);
}

// Constructor si destructor

viorel::Server::Server(int port_, int conexiuniMaxime_)
{
    if (conexiuniMaxime_ > 0)
    {
        conexiuniMaxime = conexiuniMaxime_;
    }
    else
    {
        conexiuniMaxime = SOMAXCONN;
    }
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (noProblems(sock))
    {
        std::cout << "Socket creat cu succes!" << "\n";
        std::cout << sock << "\n";
    }
    writeSocketAddress(serveradd, port_);
    memset(&serveradd.sin_zero, 0, sizeof(serveradd.sin_zero)); // <---- E practica buna sa setezi sin_zero la 0 totusi.
}

viorel::Server::~Server()
{
}

// Metode publice

void viorel::Server::namingTheSocket()
{
    if (noProblems(bind(sock, (sockaddr *)&serveradd, sizeof(serveradd))))
    {
        std::cout << "Succes la bind!\n";
    }
}

void viorel::Server::setSocketForListening()
{
    if (noProblems(listen(sock, conexiuniMaxime)))
    {
        std::cout << "Serverul asculta! \n";
    }
}

int viorel::Server::acceptingConnections()
{
    int clientAcceptat = accept(sock, NULL, NULL);
    if (noProblems(clientAcceptat))
    {
        std::cout << "Serverul a acceptat o conexiune \n";
    }
    return clientAcceptat;
}