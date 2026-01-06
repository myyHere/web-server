#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <atomic>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

extern std::atomic<size_t> g_bytes_received;
extern std::atomic<size_t> g_bytes_sent;
extern int g_port;
extern std::string g_web_root;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *labelPort;
    QLabel *labelRoot;
    QLabel *labelRecv;
    QLabel *labelSend;
    QTimer *timer;

private slots:
    void updateStats();
};

#endif // MAINWINDOW_H
