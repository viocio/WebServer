#include "server.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>

// Metode private

bool server::ServerHTTP::testForProblems(int var)
{
    bool succes;
    if (var < 0)
    {
        succes = false;
        throw std::runtime_error("Eroare la crearea socketului!\n");
        std::cout << strerror(errno) << " " << "Cod eroare: " << errno;
        return succes;
    }
    else
    {
        succes = true;
        return succes;
    }
}

void server::ServerHTTP::writeSocketAddress(sockaddr_in &serveradd, int port_)
{
    serveradd.sin_family = AF_INET;
    inet_pton(AF_INET, "172.16.1.96", &serveradd.sin_addr.s_addr);
    serveradd.sin_port = htons(port_);
}

// Constructor si destructor

server::ServerHTTP::ServerHTTP(int port_, int conexiuniMaxime_)
{
    conexiuniMaxime = conexiuniMaxime_;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (testForProblems(sock))
    {
        std::cout << "Socket creat cu succes!" << "\n";
        std::cout << sock << "\n";
    }
    writeSocketAddress(serveradd, port_);
    memset(&serveradd.sin_zero, 0, sizeof(serveradd.sin_zero)); // <---- E practica buna sa setezi sin_zero la 0 totusi.
}

server::ServerHTTP::~ServerHTTP()
{
}

// Metode publice

void server::ServerHTTP::namingTheSocket()
{
    if (testForProblems(bind(sock, (sockaddr *)&serveradd, sizeof(serveradd))))
    {
        std::cout << "Succes la bind!\n";
    }
}

void server::ServerHTTP::setSocketForListening()
{
    if (testForProblems(listen(sock, conexiuniMaxime)))
    {
        std::cout << "Serverul asculta! \n";
    }
}

void server::ServerHTTP::acceptingConnections()
{
    if (testForProblems(accept(sock, NULL, NULL)))
    {
        std::cout << "Serverul asteapta o conexiune \n";
    }
}