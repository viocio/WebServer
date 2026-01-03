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
        response = resolvePOST(request);
    else if (request.requestLine.method == "DELETE")
        response = resolveDELETE(request);
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

    ///  nu o sa ma mai complic cu pagini, trimit doar codul

    response.headers["Connection"] = "close";
    response.headers["Content-Length"] = "0";

    return response;
}

HTTPresponse notFound()
{
    // Eroare 404
    HTTPresponse response;
    response.statusLine.version = "HTTP/1.1";
    response.statusLine.code = "404";
    response.statusLine.message = "Not Found";
    response.headers["Content-Length"] = "0";
    response.headers["Connection"] = "close";
    return response;
}

/* DE implementat*/

HTTPresponse badRequest()
{
    HTTPresponse response;
    response.statusLine.version = "HTTP/1.1";
    response.statusLine.code = "400";
    response.statusLine.message = "Bad Request";
    response.headers["Content-Length"] = "0";
    response.headers["Connection"] = "close";
    return response;
}

HTTPresponse internalError()
{
    HTTPresponse response;
    response.statusLine.version = "HTTP/1.1";
    response.statusLine.code = "500";
    response.statusLine.message = "Internal Error";
    response.headers["Content-Length"] = "0";
    response.headers["Connection"] = "close";
    return response;
    return response;
}

/*    ##################        Poate mai sunt cazuri de eroare, de completat       #############*/
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

HTTPresponse resolvePOST(const HTTPrequest request)
{
    HTTPresponse response;
    std::string numeFisier;
    auto it = request.headers.find("X-filename");
    if (it != request.headers.end())
    {
        numeFisier = it->second;
    }
    else
    {
        if (request.requestLine.URI.size() > 1)
            numeFisier = request.requestLine.URI.substr(1); // "/a.txt" -> "a.txt"
    }
    if (numeFisier.empty())
        return badRequest();

    if (numeFisier.find("..") != std::string::npos || numeFisier.find("/") != std::string::npos)
        return badRequest();

    std::string pathFisier = "site/" + numeFisier;
    std::ofstream fisier(pathFisier, std::ios::binary);
    if (!fisier.is_open())
        return internalError(); // Eroare 500

    fisier.write(request.body.data(), request.body.size());
    if (!fisier)
        return internalError();

    response.statusLine.version = "HTTP/1.1";
    response.statusLine.code = "201";
    response.statusLine.message = "Created";
    response.headers["Content-Length"] = "0";
    response.headers["Connection"] = "close";
    return response;
}

/*  #################### De implementat ######################### */

HTTPresponse resolveDELETE(const HTTPrequest request)
{
    HTTPresponse response;
    std::string numeFisier;
    auto it = request.headers.find("X-filename");
    if (it != request.headers.end())
    {
        numeFisier = it->second;
    }
    else
    {
        if (request.requestLine.URI.size() > 1)
            numeFisier = request.requestLine.URI.substr(1); // "/a.txt" -> "a.txt"
    }
    if (numeFisier.empty())
        return badRequest();

    if (numeFisier.find("..") != std::string::npos || numeFisier.find("/") != std::string::npos)
        return badRequest();

    std::string pathFisier = "site/" + numeFisier;
    // nu verifica daca fisierul exista
    int status = remove(pathFisier.c_str());
    if (status == 0)
        return internalError();

    response.statusLine.version = "HTTP/1.1";
    response.statusLine.code = "200";
    response.statusLine.message = "OK";
    response.headers["Content-Length"] = "0";
    response.headers["Connection"] = "close";
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

/*  #################   De completetat  #################   */
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
        return "text/javascript";
    }
    else
    {
        return "neimplementat"; // ##########################   Atentie la ce intoarce aceasta functie in cazul default
    }
}