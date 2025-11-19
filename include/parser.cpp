#include "parser.hpp"
#include <iostream>

HTTPrequest httpRequestParser(std::string requestString)
{
    HTTPrequest request;
    std::stringstream ss(requestString);
    ss >> request.requestLine.method >> request.requestLine.URI >> request.requestLine.version;
    size_t pos = requestString.find("\n", 0);
    std::string headersAndBody = requestString.substr(pos + 1, requestString.length());
    for (;;)
    {
        if (headersAndBody.find("\r") == 0)
        {
            std::string body = headersAndBody.substr(2);
            request.body = body;
            break;
        }
        pos = headersAndBody.find(":");
        std::string key = headersAndBody.substr(0, pos);
        headersAndBody = headersAndBody.substr(pos + 1);
        pos = headersAndBody.find("\r");
        std::string value = headersAndBody.substr(0, pos);
        request.headers[key] = value;
        pos = headersAndBody.find("\n");
        headersAndBody = headersAndBody.substr(pos + 1);
    }
    return request;
}

HTTPresponse httpHandler(std::string requestString)
{
    HTTPresponse response;
    // TODO request de parsat.
    HTTPrequest httprequest = httpRequestParser(requestString);
    return response;
}