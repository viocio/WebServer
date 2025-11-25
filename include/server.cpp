#include "server.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <unistd.h>

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
    close(sock);
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

std::string viorel::Server::receivingRequest(int socketClient_)
{
    std::string request;
    // TODO: make sure the request sent to httpHandler() is full
    char buffer[2048];
    int numberBytes;
    bool headersDone = false;
    int contentLengthNumber = 0;
    while ((numberBytes = recv(socketClient_, buffer, sizeof(buffer), 0)) > 0)
    {
        request.append(buffer, numberBytes);
        if (request.find("\r\n\r\n") != std::string::npos)
        {
            break;
        }
    }
    if (request.find("Content-Length") != std::string::npos)
    {
        std::string contentLength = request.substr(request.find("Content-Length: "));
        std::string contentLengthEnd = contentLength.substr(0, contentLength.find("\r\n"));
        contentLength = contentLengthEnd.substr(contentLength.find(": ") + 2);
        contentLength = contentLength.substr(0, contentLength.find("\r\n"));
        contentLengthNumber = stoi(contentLength);
    }
    if (contentLengthNumber == 0)
    {
        return request;
    }
    size_t alreadyReceivedBody = request.find("\r\n\r\n") + 4;
    int remainingBody = contentLengthNumber - (request.size() - alreadyReceivedBody);
    while (remainingBody > 0)
    {
        numberBytes = recv(socketClient_, buffer, sizeof(buffer), 0);
        if (numberBytes <= 0)
            break;
        request.append(buffer, numberBytes);
        remainingBody -= numberBytes;
    }
    return request;
}