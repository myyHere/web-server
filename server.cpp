#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")

std::atomic<size_t> g_bytes_received{0};
std::atomic<size_t> g_bytes_sent{0};

// 处理单个客户端
void handle_client(SOCKET client, const std::string &web_root)
{
    char buffer[4096] = {0};
    int len = recv(client, buffer, sizeof(buffer) - 1, 0);
    if (len <= 0)
    {
        closesocket(client);
        return;
    }
    g_bytes_received += len; // 累加接收流量

    std::string request(buffer, len);
    std::cout << "收到请求:\n"
              << request << std::endl;

    // 解析请求行
    std::istringstream iss(request);
    std::string method, path, version;
    iss >> method >> path >> version;

    if (method != "GET")
    {
        std::string resp =
            "HTTP/1.1 405 Method Not Allowed\r\n"
            "Content-Length: 0\r\n\r\n";
        send(client, resp.c_str(), resp.size(), 0);
        g_bytes_sent += resp.size();
        closesocket(client);
        return;
    }

    if (path.back() == '/')
    {
        path += "index.html";
    }

    std::string full_path = web_root + path;
    std::ifstream file(full_path, std::ios::binary);

    if (!file.is_open())
    {
        std::string body = "<h1>404 Not Found</h1>";
        std::ostringstream oss;
        oss << "HTTP/1.1 404 Not Found\r\n"
            << "Content-Type: text/html\r\n"
            << "Content-Length: " << body.size() << "\r\n\r\n"
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
    oss << "HTTP/1.1 200 OK\r\n"
        << "Content-Type: text/html\r\n"
        << "Content-Length: " << body.size() << "\r\n\r\n"
        << body;

    std::string resp = oss.str();
    send(client, resp.c_str(), resp.size(), 0);
    g_bytes_sent += resp.size();

    closesocket(client);
}

// 主函数
int main(int argc, char *argv[])
{
    int port = 8000;                // 默认端口
    std::string web_root = "./www"; // 默认根目录

    // 支持命令行指定端口和根目录
    if (argc >= 2)
        port = std::stoi(argv[1]);
    if (argc >= 3)
        web_root = argv[2];

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET)
    {
        std::cerr << "Socket 创建失败\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind 失败\n";
        closesocket(server);
        WSACleanup();
        return 1;
    }

    listen(server, 5);

    std::cout << "Web Server 启动，端口 " << port
              << ", 根目录: " << web_root << std::endl;

    while (true)
    {
        SOCKET client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET)
            continue;

        std::thread(handle_client, client, web_root).detach();

        // 输出流量统计
        std::cout << "已接收: " << g_bytes_received.load()
                  << " 字节, 已发送: " << g_bytes_sent.load() << " 字节\n";
    }

    closesocket(server);
    WSACleanup();
    return 0;
}
