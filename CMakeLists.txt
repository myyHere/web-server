cmake_minimum_required(VERSION 3.16)

project(QtWebServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 的三件套，ui 必开
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt6 写法
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QtWebServer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    webserver.cpp
    webserver.h
    test/index.html test/s.html www/index.html
)

target_link_libraries(QtWebServer
    Qt6::Widgets
    ws2_32
)
