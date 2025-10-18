#include <iostream>
#include "server.hpp"

int main()
{
    int port;
    std::cout << "Portul pe care vrei sa deschizi serverul: " << "\n";
    std::cin >> port;
    server::ServerHTTP serverHTTP(port);
}