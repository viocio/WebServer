#include "parser.hpp"
#include <iostream>
#include <fstream>

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
        headersAndBody = headersAndBody.substr(pos + 2);
        pos = headersAndBody.find("\r");
        std::string value = headersAndBody.substr(0, pos);
        request.headers[key] = value;
        pos = headersAndBody.find("\n");
        headersAndBody = headersAndBody.substr(pos + 1);
    }
    return request;
}

HTTPresponse responseConstructor(const HTTPrequest request, std::string pathRelativ)
{
    // TODO: construct a response based on request
    HTTPresponse response;

    if (request.requestLine.method == "GET")
        response = resolveGET(request, pathRelativ);
    else if (request.requestLine.method == "POST")
        response = resolvePOST(request, pathRelativ);
    else if (request.requestLine.method == "DELETE")
        response = resolveDELETE(request, pathRelativ);
    else
        response = notImplemented();
    return response;
}

HTTPresponse notImplemented()
{
    HTTPresponse response;
    response.statusLine.version = "HTTP/1.1";
    response.statusLine.code = "501";
    response.statusLine.message = "Not Implemented";

    response.headers["Content-Type"] = "text/html";
    // response.headers["Content-Length"] = std::to_string(sizeof(fisier));

    return response;
}

HTTPresponse notFound()
{
    // Eroare 404
    HTTPresponse response;
    return response;
}

HTTPresponse resolveGET(const HTTPrequest request, std::string pathRelativ)
{
    HTTPresponse response;
    response.statusLine.version = "HTTP/1.1";
    std::string path = "";
    if (request.requestLine.URI == "/")
    {
        path = pathRelativ + "index.html";
    }
    else
    {
        path = pathRelativ + request.requestLine.URI.substr(1);
    }
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        return notFound();
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    response.body = ss.str();
    response.headers["Content-Type"] = setContentType(path);
    response.headers["Content-Length"] = std::to_string(response.body.size());
    response.statusLine.code = "200";
    response.statusLine.message = "OK";
    return response;
}

HTTPresponse resolvePOST(const HTTPrequest request, std::string pathRelativ)
{
    HTTPresponse response;
    return response;
}

HTTPresponse resolveDELETE(const HTTPrequest request, std::string pathRelativ)
{
    HTTPresponse response;
    return response;
}

std::string httpHandler(std::string requestString, std::string pathRelativ)
{
    HTTPresponse response;
    std::string responseS;
    // TODO request de parsat.
    HTTPrequest httprequest = httpRequestParser(requestString);
    response = responseConstructor(httprequest, pathRelativ);
    responseS = rtos(response);
    return responseS;
}

// functii suport

std::string rtos(HTTPresponse response)
{
    std::string responseS;
    // TODO: stringify the response
    responseS = response.statusLine.version + " " + response.statusLine.code + " " + response.statusLine.message + "\r\n";
    for (auto it : response.headers)
    {
        responseS += it.first + ": " + it.second + "\r\n";
    }
    responseS += "\r\n";
    responseS += response.body;
    return responseS;
}

std::string setContentType(std::string path)
{
    std::string extensie;
    extensie = path.substr(path.find(".") + 1);
    if (extensie == "html")
    {
        return "text/html";
    }
    else if (extensie == "css")
    {
        return "text/css";
    }
    else if (extensie == "js")
    {
        return "application/javascript";
    }
    else
    {
        return "neimplementat"; // ##########################   Atentie la ce intoarce aceasta functie in cazul default
    }
}