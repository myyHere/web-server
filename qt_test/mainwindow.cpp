#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    labelPort = new QLabel(this);
    labelRoot = new QLabel(this);
    labelRecv = new QLabel(this);
    labelSend = new QLabel(this);

    layout->addWidget(labelPort);
    layout->addWidget(labelRoot);
    layout->addWidget(labelRecv);
    layout->addWidget(labelSend);

    setCentralWidget(central);
    setWindowTitle("Simple Web Server");

    // 初始化显示
    labelPort->setText(QString("Port: %1").arg(g_port));
    labelRoot->setText(QString("Web Root: %1").arg(QString::fromStdString(g_web_root)));

    // 定时刷新
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateStats);
    timer->start(500); // 每 0.5 秒刷新一次
}

MainWindow::~MainWindow() {}

void MainWindow::updateStats()
{
    labelRecv->setText(QString("Bytes Received: %1").arg(g_bytes_received.load()));
    labelSend->setText(QString("Bytes Sent: %1").arg(g_bytes_sent.load()));
}
