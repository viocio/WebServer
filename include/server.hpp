#ifndef SERVER_HTTP
#define SERVER_HTTP
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

namespace viorel
{
    class Server
    {
    private:
        int sock = 0;
        int conexiuniMaxime = 0;
        sockaddr_in serveradd;
        std::string ipServer;
        void writeSocketAddress(sockaddr_in &serveradd, int port_, std::string ip);
        std::string extractOne(std::string &pending);

    public:
        Server(int port_, int conexiuniMaxime_, std::string ipServer);
        ~Server();
        bool noProblems(int var); // verificam daca functiile de socket au avut succes
        void namingTheSocket();
        void setSocketForListening();
        int acceptingConnections();
        std::string receivingRequest(int socketClient_, bool &postIncomplet, std::string &pending);
        void sendData(const std::string response, int socketClient);
    };
}
#endif