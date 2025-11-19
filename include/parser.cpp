#include "parser.hpp"

HTTPrequest httpRequestParser(std::string requestString)
{
    HTTPrequest request;
    return request;
}

HTTPresponse httpHandler(std::string requestString)
{
    HTTPresponse response;
    // TODO request de parsat.
    HTTPrequest httprequest = httpRequestParser(requestString);
    return response;
}