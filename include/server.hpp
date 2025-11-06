#ifndef SERVER_HTTP
#define SERVER_HTTP
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace server
{
    class ServerHTTP
    {
    private:
        int sock = 0;
        sockaddr_in serveradd;
        void writeSocketAddress(sockaddr_in &serveradd, int port_);
        int conexiuniMaxime = 0;

    public:
        ServerHTTP(int port_, int conexiuniMaxime_);
        ~ServerHTTP();
        bool testForProblems(int var); // verificam daca functiile de socket au avut succes
        void namingTheSocket();
        void setSocketForListening();
        void acceptingConnections();
    };
}
#endif