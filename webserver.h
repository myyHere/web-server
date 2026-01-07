#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <atomic>
#include <string>
#include <map>

#pragma comment(lib, "ws2_32.lib")

class WebServer
{
public:
    WebServer();
    ~WebServer() = default;

    void start(int port, const std::string &root);

    size_t bytesReceived() const { return recvBytes.load(); }
    size_t bytesSent() const { return sendBytes.load(); }

private:
    void serverLoop(int port, std::string root);
    void handleClient(SOCKET client, std::string root);

private:
    std::atomic<size_t> recvBytes;
    std::atomic<size_t> sendBytes;
    std::atomic<bool> running;
};
