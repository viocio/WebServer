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

// functie de intrare

std::string httpHandler(std::string requestString, std::string pathRelativ);

// metoda care ruteaza catre raspunsuri

HTTPresponse responseConstructor(const HTTPrequest request, std::string pathRelativ);

// functii care intorc raspunsuri

HTTPresponse resolveGET(const HTTPrequest request, std::string pathRelativ);
HTTPresponse resolvePOST(const HTTPrequest request, std::string pathRelativ);
HTTPresponse resolveDELETE(const HTTPrequest request, std::string pathRelativ);
HTTPresponse notImplemented();
HTTPresponse notFound();

// functii suport

std::string setContentType(std::string path);
std::string rtos(HTTPresponse response);
HTTPrequest httpRequestParser(std::string requestString);

#endif