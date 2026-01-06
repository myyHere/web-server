#include "mainwindow.h"
#include <QApplication>
#include <thread>
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")

std::atomic<size_t> g_bytes_received{0};
std::atomic<size_t> g_bytes_sent{0};
int g_port = 8000;
std::string g_web_root = "./www";

// 这里复用你现有 handle_client 函数
void handle_client(SOCKET client, const std::string &web_root)
{
    char buffer[4096] = {0};
    int len = recv(client, buffer, sizeof(buffer) - 1, 0);
    if (len <= 0)
    {
        closesocket(client);
        return;
    }
    g_bytes_received += len;

    std::string request(buffer, len);
    std::istringstream iss(request);
    std::string method, path, version;
    iss >> method >> path >> version;

    if (method != "GET")
    {
        std::string resp = "HTTP/1.1 405 Method Not Allowed\r\nContent-Length:0\r\n\r\n";
        send(client, resp.c_str(), resp.size(), 0);
        g_bytes_sent += resp.size();
        closesocket(client);
        return;
    }

    if (path.back() == '/')
        path += "index.html";

    std::string full_path = web_root + path;
    std::ifstream file(full_path, std::ios::binary);
    if (!file.is_open())
    {
        std::string body = "<h1>404 Not Found</h1>";
        std::ostringstream oss;
        oss << "HTTP/1.1 404 Not Found\r\nContent-Type:text/html\r\nContent-Length:"
            << body.size() << "\r\n\r\n"
            << body;
        std::string resp = oss.str();
        send(client, resp.c_str(), resp.size(), 0);
        g_bytes_sent += resp.size();
        closesocket(client);
        return;
    }

    std::ostringstream content;
    content << file.rdbuf();
    std::string body = content.str();
    std::ostringstream oss;
    oss << "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nContent-Length:"
        << body.size() << "\r\n\r\n"
        << body;
    std::string resp = oss.str();
    send(client, resp.c_str(), resp.size(), 0);
    g_bytes_sent += resp.size();
    closesocket(client);
}

// 服务器线程函数
void serverThread()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(g_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (sockaddr *)&addr, sizeof(addr));
    listen(server, 5);

    std::cout << "Server started on port " << g_port << ", root: " << g_web_root << std::endl;

    while (true)
    {
        SOCKET client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET)
            continue;
        std::thread(handle_client, client, g_web_root).detach();
    }

    closesocket(server);
    WSACleanup();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 命令行参数设置端口和根目录
    if (argc >= 2)
        g_port = std::stoi(argv[1]);
    if (argc >= 3)
        g_web_root = argv[2];

    // 启动服务器线程
    std::thread t(serverThread);
    t.detach();

    MainWindow w;
    w.show();
    return a.exec();
}
