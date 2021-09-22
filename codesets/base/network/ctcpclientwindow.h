#ifndef CTCPCLIENTWINDOW_H
#define CTCPCLIENTWINDOW_H

#include <QMainWindow>
#include    <QTcpSocket>
#include    <QLabel>

namespace Ui {
class TcpClientWindow;
}

class CTcpClientWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTcpSocket  *tcpClient;  //socket
    QLabel  *LabSocketState;  //状态栏显示标签

    QString getLocalIP();//获取本机IP地址
protected:
    void    closeEvent(QCloseEvent *event);
public:
    explicit CTcpClientWindow(QWidget *parent = 0);
    ~CTcpClientWindow();

private slots:
//自定义槽函数
    void    onConnected();
    void    onDisconnected();
    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onSocketReadyRead();//读取socket传入的数据
//
    void on_actConnect_triggered();

    void on_actDisconnect_triggered();

    void on_actClear_triggered();

    void on_btnSend_clicked();

private:
    Ui::TcpClientWindow *ui;
};

#endif // CTCPCLIENTWINDOW_H
