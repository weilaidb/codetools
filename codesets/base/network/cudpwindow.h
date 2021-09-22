#ifndef CUDPWINDOW_H
#define CUDPWINDOW_H

#include <QMainWindow>

#include    <QUdpSocket>
#include    <QLabel>

namespace Ui {
class UdpWindow;
}


class CUdpWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel  *LabSocketState;//socket状态显示标签
    QUdpSocket  *udpSocket;//
    QString getLocalIP();//获取本机IP地址

public:
    explicit CUdpWindow(QWidget *parent = 0);
    ~CUdpWindow();

private slots:
//自定义槽函数
    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onSocketReadyRead();//读取socket传入的数据
//
    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_actClear_triggered();

    void on_btnSend_clicked();

    void on_actHostInfo_triggered();

    void on_btnBroadcast_clicked();

private:
    Ui::UdpWindow *ui;
};

#endif // CUDPWINDOW_H
