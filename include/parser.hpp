#ifndef PARSER
#define PARSER

#include <string>
#include <unordered_map>
#include <sstream>

// structuri de date

struct RequestLine
{
    std::string method;
    std::string URI;
    std::string version;
};

struct StatusLine
{
    std::string version;
    std::string code;
    std::string message;
};

struct HTTPrequest
{
    RequestLine requestLine;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

struct HTTPresponse
{
    StatusLine statusLine;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

// functii

HTTPrequest httpRequestParser(std::string requestString);
HTTPresponse httpHandler(std::string requestString);

#endif