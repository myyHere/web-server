#include "webserver.h"
#include <fstream>
#include <sstream>
#include <iostream>

WebServer::WebServer()
    : recvBytes(0), sendBytes(0), running(false)
{
}

void WebServer::start(int port, const std::string &root)
{
    if (running)
        return;

    running = true;
    std::thread(&WebServer::serverLoop, this, port, root).detach();
}

void WebServer::serverLoop(int port, std::string root)
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&addr, sizeof(addr));
    listen(serverSock, 5);

    while (running)
    {
        SOCKET client = accept(serverSock, NULL, NULL);
        if (client == INVALID_SOCKET)
            continue;

        std::thread([this, client, root]() {
            this->handleClient(client, root);
        }).detach();
    }

    closesocket(serverSock);
    WSACleanup();
}

void WebServer::handleClient(SOCKET client, std::string root)
{
    char buffer[8192];

    int len = recv(client, buffer, sizeof(buffer) - 1, 0);
    if (len <= 0)
    {
        closesocket(client);
        return;
    }

    recvBytes += len;

    std::string request(buffer, len);
    std::istringstream iss(request);
    std::string method, path, version;
    iss >> method >> path >> version;

    std::string responseBody;

    if (method == "GET")
    {
        if (path == "/") path = "/index.html";

        std::ifstream file(root + path, std::ios::binary);
        if (!file.is_open())
        {
            responseBody = "<h1>404 Not Found</h1>";
        }
        else
        {
            std::ostringstream content;
            content << file.rdbuf();
            responseBody = content.str();
        }
    }
    else if (method == "POST")
    {
        size_t pos = request.find("\r\n\r\n");
        std::string body;
        if (pos != std::string::npos)
            body = request.substr(pos + 4);

        std::map<std::string, std::string> params;
        std::istringstream bodyStream(body);
        std::string pair;
        while (std::getline(bodyStream, pair, '&'))
        {
            size_t eq = pair.find('=');
            if (eq != std::string::npos)
            {
                std::string key = pair.substr(0, eq);
                std::string value = pair.substr(eq + 1);
                params[key] = value;
            }
        }

        responseBody = "<h1>POST 数据已接收</h1>";
        for (auto &kv : params)
        {
            responseBody += "<p>" + kv.first + " = " + kv.second + "</p>";
        }
    }
    else
    {
        responseBody = "<h1>501 Not Implemented</h1>";
    }

    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\n"
        << "Content-Type: text/html; charset=UTF-8\r\n"
        << "Content-Length: " << responseBody.size() << "\r\n"
        << "\r\n"
        << responseBody;


    // oss << "HTTP/1.1 200 OK\r\n"
    //     << "Content-Type: text/html; charset=UTF-8\r\n"
    //     << "Content-Length: " << body.size() << "\r\n\r\n"
    //     << body;


    std::string resp = oss.str();
    int sent = send(client, resp.c_str(), resp.size(), 0);
    if (sent > 0)
        sendBytes += sent;

    closesocket(client);
}
