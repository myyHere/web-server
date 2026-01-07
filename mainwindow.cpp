#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString projectRoot = "D:/Documents/QtWebServer"; // 根目录
    ui->portEdit_4->setText("8000");
    ui->rootEdit_4->setText(projectRoot + "/www");

    connect(ui->startBtn_4, &QPushButton::clicked, this, [=]() {
        int port = ui->portEdit_4->text().toInt();
        server.start(port, ui->rootEdit_4->text().toStdString());

        ui->startBtn_4->setEnabled(false);
        ui->startBtn_4->setText("服务器运行中...");
    });

    connect(&timer, &QTimer::timeout, this, [=]() {
        ui->recvLabel_4->setText(
            QString("已接收: %1 字节").arg(server.bytesReceived()));
        ui->sendLabel_4->setText(
            QString("已发送: %1 字节").arg(server.bytesSent()));
    });

    timer.start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}
