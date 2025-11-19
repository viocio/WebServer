#include <iostream>
#include "parser.hpp"

int main()
{
    std::string getReq =
        "GET / HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "User-Agent: TestClient/1.0\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n"
        "\r\n";

    HTTPrequest request = httpRequestParser(getReq);
    std::cout << request.requestLine.method << " " << request.requestLine.URI << " " << request.requestLine.version << std::endl;
    for (auto i : request.headers)
    {
        std::cout << i.first << ":" << i.second << std::endl;
    }
    std::cout << request.body;
    return 0;
}