# Qt Web Server 应用

一个基于Qt框架和Windows Socket API的简单Web服务器应用，提供GUI界面进行配置和管理。

## 功能特性

- **HTTP服务器** - 基于Winsock API实现的Windows平台Web服务器
- **GET请求处理** - 支持静态文件提供，自动映射`/`到`index.html`
- **POST请求处理** - 支持表单数据解析和处理
- **图形化界面** - 使用Qt6开发的用户友好界面
- **实时统计** - 显示接收和发送的字节数统计
- **多线程处理** - 为每个客户端连接创建独立线程

## 技术栈

- **编程语言** - C++17
- **GUI框架** - Qt6
- **网络API** - Windows Socket API (Winsock2)
- **构建系统** - CMake
- **编译器** - MinGW 64-bit (g++)

## 项目结构

```
web-server/
├── CMakeLists.txt       # CMake构建配置
├── main.cpp             # 应用程序入口
├── mainwindow.h         # 主窗口头文件
├── mainwindow.cpp       # 主窗口实现
├── mainwindow.ui        # UI设计文件
├── webserver.h          # WebServer类头文件
├── webserver.cpp        # WebServer类实现
├── www/                 # Web服务的静态文件目录
│   └── index.html
├── test/                # 测试HTML文件
│   ├── index.html
│   └── s.html
└── build/               # 构建输出目录
```

## 核心类说明

### WebServer 类

核心服务器类，负责HTTP服务的实现。

**主要成员函数：**
- `start(int port, const std::string &root)` - 启动服务器
- `bytesReceived()` - 获取已接收字节数
- `bytesSent()` - 获取已发送字节数

**核心实现：**
- `serverLoop()` - 服务器主循环，接受客户端连接
- `handleClient()` - 处理单个客户端请求

### MainWindow 类

Qt GUI主窗口类，提供用户交互界面。

**功能：**
- 端口号输入框 - 设置服务器监听端口
- 根目录输入框 - 设置Web文件根目录
- 启动按钮 - 启动Web服务器
- 统计信息显示 - 实时显示字节数统计

## 使用方法

### 1. 编译

使用CMake进行编译（需要安装Qt6和MinGW）：

```bash
cd build
cmake ..
cmake --build .
```

或在Visual Studio Code中使用C++构建任务。

### 2. 运行

执行编译后的可执行文件：

```bash
QtWebServer.exe
```

### 3. 配置

在GUI界面中：
1. 输入要监听的端口号（默认8000）
2. 输入Web文件根目录路径（如：`D:/Documents/QtWebServer/www`）
3. 点击"启动"按钮启动服务器

### 4. 访问服务器

启动后可通过浏览器访问：
```
http://localhost:8000/
http://localhost:8000/index.html
```

## HTTP协议支持

### GET 请求
- 返回指定路径的文件内容
- 路径`/`自动映射到`/index.html`
- 文件不存在时返回404错误

### POST 请求
- 解析表单数据（URL编码格式）
- 返回接收到的参数列表

### HTTP响应格式
```
HTTP/1.1 200 OK
Content-Type: text/html; charset=UTF-8
Content-Length: <size>

<response body>
```

## 依赖项

- **系统库** - ws2_32 (Windows Socket库)
- **Qt6** - Core, Gui, Widgets模块
- **C++标准库** - thread, atomic, string, map

## 注意事项

- 仅支持Windows平台（使用了Winsock API）
- 服务器使用detached线程，应用关闭时可能未完全清理
- 暂不支持HTTPS
- 不处理HTTP header中的Content-Encoding
- 静态文件路径使用相对项目根目录的相对路径

## 可能的改进

- [ ] 添加线程池管理连接
- [ ] 支持更多MIME类型
- [ ] 添加日志记录功能
- [ ] 支持HTTP keep-alive
- [ ] 添加请求超时控制
- [ ] 跨平台支持（Linux/macOS）
- [ ] HTTPS支持

## 许可证

该项目仅作学习之用。
