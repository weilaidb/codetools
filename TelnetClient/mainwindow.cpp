#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    telnet = new QtTelnet(this);

    connect(telnet, SIGNAL(message(const QString &)),this, SLOT(telnetMessage(const QString &)));
    connect(telnet, SIGNAL(loginRequired()),this, SLOT(telnetLoginRequired()));
    connect(telnet, SIGNAL(loginFailed()),this, SLOT(telnetLoginFailed()));
    connect(telnet, SIGNAL(loggedOut()),this, SLOT(telnetLoggedOut()));
    connect(telnet, SIGNAL(loggedIn()),this, SLOT(telnetLoggedIn()));
    connect(telnet, SIGNAL(connectionError(QAbstractSocket::SocketError)),
            this, SLOT(telnetConnectionError(QAbstractSocket::SocketError)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::telnetMessage(const QString &msg)
{
    ui->te_Msg->append(msg);
}

void MainWindow::telnetLoginRequired()
{
    QString user = ui->le_User->text();
    QString passwd  = ui->le_Passwd->text();

    if(user == "" || passwd == "")
    {
        ui->te_Msg->append("用户名和密码不能为空!");
        return;
    }
    telnet->login(user,passwd); // 登入telnet
    // telnet->logout(); // 登出
}

void MainWindow::telnetLoginFailed()
{
    ui->te_Msg->append("登录失败!");
}

void MainWindow::telnetLoggedOut()
{
    ui->te_Msg->append("登出成功!");
}

void MainWindow::telnetLoggedIn()
{
    ui->te_Msg->append("登录成功!");
}

void MainWindow::telnetConnectionError(QAbstractSocket::SocketError error)
{
    ui->te_Msg->append(QString("连接错误: %1").arg(error));
}

void MainWindow::on_pb_Link_clicked()
{
    QString host = ui->le_Host->text();
    if(host == "")
    {
        ui->te_Msg->append("IP地址不能为空!");
        return ;
    }
    telnet->connectToHost(host);


}

void MainWindow::on_pb_close_clicked()
{
    telnet->close();
}

void MainWindow::on_pb_Send_clicked()
{
    QString cmd = ui->le_SendText->text() + "\r\n" ;
    telnet->sendData(cmd);
}
