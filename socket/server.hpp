#ifndef SERVER_HTTP
#define SERVER_HTTP
#include <stdio.h>

namespace server
{
    class ServerHTTP
    {
    private:
        int sock = 0;

    public:
        ServerHTTP(int port_);
        ~ServerHTTP();
    };
}
#endif