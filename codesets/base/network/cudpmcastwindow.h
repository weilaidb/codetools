#ifndef CUDPMCASTWINDOW_H
#define CUDPMCASTWINDOW_H

#include <QMainWindow>

#include    <QMainWindow>

#include    <QUdpSocket>
#include    <QLabel>

namespace Ui {
class UdpMcastWindow;
}

class CUdpMcastWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel  *LabSocketState;
    QUdpSocket  *udpSocket;//用于与连接的客户端通讯的QTcpSocket
    QHostAddress    groupAddress;//组播地址
    QString getLocalIP();//获取本机IP地址
public:
    explicit CUdpMcastWindow(QWidget *parent = 0);
    ~CUdpMcastWindow();

private slots:
    //自定义槽函数
    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onSocketReadyRead();//读取socket传入的数据
    //
    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_actClear_triggered();

    void on_actHostInfo_triggered();

    void on_btnMulticast_clicked();

private:
    Ui::UdpMcastWindow *ui;

};

#endif // CUDPMCASTWINDOW_H
