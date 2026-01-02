#include "server.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>

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

void viorel::Server::writeSocketAddress(sockaddr_in &serveradd, int port_)
{
    serveradd.sin_family = AF_INET;
    inet_pton(AF_INET, "172.16.123.11", &serveradd.sin_addr.s_addr);
    serveradd.sin_port = htons(port_);
}

std::string viorel::Server::extractOne(std::string &pending)
{
    size_t pos = pending.find("\r\n\r\n");
    std::string request = pending.substr(0, pos + 4);
    pending = pending.substr(pos + 4);
    return request;
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

void viorel::Server::sendData(const std::string response, int socketClient_)
{
    int numberOfBytesSent = 0;
    int totalNumberOfBytes = response.size();
    char const *responseToSend = response.c_str();
    do
    {
        numberOfBytesSent = send(socketClient_, responseToSend, totalNumberOfBytes, 0);
        responseToSend += numberOfBytesSent;
        totalNumberOfBytes -= numberOfBytesSent;
    } while (totalNumberOfBytes > 0);
}

std::string viorel::Server::receivingRequest(int socketClient_, bool &postIncomplet, std::string &pending)
{
    if ((pending.find("GET") != std::string::npos && pending.find("\r\n\r\n") != std::string::npos))
    {
        return extractOne(pending);
    }
    postIncomplet = false;
    // TODO: make sure the request sent to httpHandler() is full
    char buffer[2048];
    int numberBytes;
    size_t contentLengthNumber = 0;
    while ((numberBytes = recv(socketClient_, buffer, sizeof(buffer), 0)) > 0)
    {
        pending.append(buffer, numberBytes);
        if (pending.find("\r\n\r\n") != std::string::npos)
        {
            break;
        }
    }
    if (numberBytes <= 0)
    {
        return "";
    }
    if (pending.find("Content-Length") != std::string::npos)
    {
        // NOTE: Content-Length parsing is strict (expects "Content-Length: ")
        // Acceptable for LAN usage; relax if needed later.

        std::string contentLength = pending.substr(pending.find("Content-Length: "));
        std::string contentLengthEnd = contentLength.substr(0, contentLength.find("\r\n"));
        contentLength = contentLengthEnd.substr(contentLength.find(": ") + 2);
        contentLengthNumber = stoi(contentLength);
    }
    if (contentLengthNumber == 0 || pending.find("Content-Length") == std::string::npos)
    {
        return pending;
    }
    size_t bodyStart = pending.find("\r\n\r\n") + 4;
    size_t alreadyReceivedBody = pending.size() - bodyStart;
    size_t remainingBody = contentLengthNumber - alreadyReceivedBody;

    if (remainingBody == 0)
    {
        return pending;
    }
    do
    {
        numberBytes = recv(socketClient_, buffer, sizeof(buffer), 0);
        if (numberBytes <= 0)
        {
            if (alreadyReceivedBody > 0)
                postIncomplet = true;
            break;
        }
        pending.append(buffer, numberBytes);
        remainingBody -= numberBytes;
    } while (remainingBody > 0);
    return pending;
}