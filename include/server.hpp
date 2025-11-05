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

    public:
        ServerHTTP(int port_);
        ~ServerHTTP();
    };
}
#endif