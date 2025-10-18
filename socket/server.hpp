#ifndef SERVER_HTTP
#define SERVER_HTTP
#include <stdio.h>

namespace server
{
    class ServerHTTP
    {
    private:
    public:
        ServerHTTP(int port_);
        ~ServerHTTP();
    };
}
#endif