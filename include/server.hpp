#ifndef SERVER_HTTP
#define SERVER_HTTP
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace viorel
{
    class Server
    {
    private:
        int sock = 0;
        sockaddr_in serveradd;
        void writeSocketAddress(sockaddr_in &serveradd, int port_);
        int conexiuniMaxime = 0;

    public:
        Server(int port_, int conexiuniMaxime_);
        ~Server();
        bool noProblems(int var); // verificam daca functiile de socket au avut succes
        void namingTheSocket();
        void setSocketForListening();
        int acceptingConnections();
    };
}
#endif