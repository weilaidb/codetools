#include "ccmdwindow.h"
#include "ui_cmd.h"
#include "csystempub.h"

#include <qDebug>
#include <QShortcut>
#include <QTextCodec>

CCmdWindow::CCmdWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CmdWindow)
{
    setWindowTitle("cmd text");

    ui->setupUi(this);
    ui->lineEdit->setText(tr("ping www.baidu.com"));
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);

    /* 新建process */
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);

    /* 回车 */
    ui->pushButton_Enter->setFocus();
    ui->pushButton_Enter->setShortcut(QKeySequence::InsertParagraphSeparator);
    ui->pushButton_Enter->setShortcut(Qt::Key_Enter);
    ui->pushButton_Enter->setShortcut(Qt::Key_Return);

    /* 按键相关 */
    connect(ui->pushButton,SIGNAL(clicked()),ui->lineEdit,SLOT(clear()));                           //清除命令行
    connect(ui->pushButton_Enter,SIGNAL(clicked()),this,SLOT(write_cmd()));                         //回车按钮
    connect(ui->pushButton_Clear,SIGNAL(clicked()),ui->textEdit,SLOT(clear()));                     //清除文本框按钮

    /* 命令行相关 */
    connect(process,SIGNAL(readyRead()),this,SLOT(read_data()));                                    //读命令行数据
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(read_data()));                      //读命令行标准数据（兼容）
    connect(process,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(error_process()));      //命令行错误处理
    connect(process,SIGNAL(finished(int)),this,SLOT(finished_process()));                           //命令行结束处理

    /* 焦点相关 */
    connect(ui->pushButton,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));
    connect(ui->pushButton_Enter,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));
    connect(ui->pushButton_Clear,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));

    process->start("cmd.exe");
}

CCmdWindow::~CCmdWindow()
{
    /* 关闭cmd */
    process->close();

    /* 释放空间 */
    delete ui;
    delete process;

    /* 拴住 */
    ui = NULL;
    process = NULL;

    /* 信息输出 */
    qDebug() << "end Process" << endl;
}

void CCmdWindow::write_cmd()
{
    /* 获得命令，\r\n代替键盘的Enter，没有则不会执行 */
    QString cmd = ui->lineEdit->text() + "\r\n";
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();

    CSystemPub::setCodecGBK();

    /* 转为char*并写入 */
    QByteArray qbarr = cmd.toLocal8Bit();
    char *ch = qbarr.data();
    qint64 len = cmd.length();
    process->write(ch, len);

    /* 信息输出 */
    qDebug() << "Success:write_cmd：" << cmd << endl;
}

void CCmdWindow::read_data()
{
    CSystemPub::setCodecGBK();
    /* 接收数据 */
    QByteArray bytes = process->readAll();

    /* 显示 */
    QString msg = QString::fromLocal8Bit(bytes);
    ui->textEdit->append(msg);
    ui->textEdit->update();

    /* 信息输出 */
    qDebug() << "Success:read_data:" << msg << endl;

}

void CCmdWindow::finished_process()
{
    /* 接收数据 */
    int flag = process->exitCode();

    /* 信息输出 */
    qDebug() << "Success:finishedProcess():" << flag << endl;
}

void CCmdWindow::error_process()
{
    /* 接收数据 */
    int err_code  = process->exitCode();
    QString err = process->errorString();

    /* 显示 */
    ui->textEdit->append(QString("error coed:%1").arg(err_code));
    ui->textEdit->append(err);

    /* 信息输出 */
    qDebug() << "Success:error_process():" << err << endl;
}
