#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qttelnet.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QtTelnet * telnet ;
private:
    Ui::MainWindow *ui;

private slots:
    void telnetMessage(const QString &);
    void telnetLoginRequired(); //
    void telnetLoginFailed();  // 登录失败
    void telnetLoggedOut();  // 退出成功
    void telnetLoggedIn();  // 登录成功
    void telnetConnectionError(QAbstractSocket::SocketError);  // 连接错误
    void on_pb_Link_clicked();
    void on_pb_close_clicked();
    void on_pb_Send_clicked();
};

#endif // MAINWINDOW_H
