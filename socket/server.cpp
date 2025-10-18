#include "server.hpp"
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>
#include <cstring>

server::ServerHTTP::ServerHTTP(int port_)
{
    if (sock = socket(AF_INET, SOCK_STREAM, 0) < 0)
    {
        throw std::runtime_error("Eroare la crearea socketului!\n");
        std::cout << strerror(errno) << " " << "Cod eroare: " << errno;
    }
    else
    {
        std::cout << "Socket creat cu succes!" << "\n";
    }
}

server::ServerHTTP::~ServerHTTP()
{
}