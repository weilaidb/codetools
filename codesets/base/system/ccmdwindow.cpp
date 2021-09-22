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

    /* �½�process */
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);

    /* �س� */
    ui->pushButton_Enter->setFocus();
    ui->pushButton_Enter->setShortcut(QKeySequence::InsertParagraphSeparator);
    ui->pushButton_Enter->setShortcut(Qt::Key_Enter);
    ui->pushButton_Enter->setShortcut(Qt::Key_Return);

    /* ������� */
    connect(ui->pushButton,SIGNAL(clicked()),ui->lineEdit,SLOT(clear()));                           //���������
    connect(ui->pushButton_Enter,SIGNAL(clicked()),this,SLOT(write_cmd()));                         //�س���ť
    connect(ui->pushButton_Clear,SIGNAL(clicked()),ui->textEdit,SLOT(clear()));                     //����ı���ť

    /* ��������� */
    connect(process,SIGNAL(readyRead()),this,SLOT(read_data()));                                    //������������
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(read_data()));                      //�������б�׼���ݣ����ݣ�
    connect(process,SIGNAL(errorOccurred(QProcess::ProcessError)),this,SLOT(error_process()));      //�����д�����
    connect(process,SIGNAL(finished(int)),this,SLOT(finished_process()));                           //�����н�������

    /* ������� */
    connect(ui->pushButton,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));
    connect(ui->pushButton_Enter,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));
    connect(ui->pushButton_Clear,SIGNAL(clicked()),ui->lineEdit,SLOT(setFocus()));

    process->start("cmd.exe");
}

CCmdWindow::~CCmdWindow()
{
    /* �ر�cmd */
    process->close();

    /* �ͷſռ� */
    delete ui;
    delete process;

    /* ˩ס */
    ui = NULL;
    process = NULL;

    /* ��Ϣ��� */
    qDebug() << "end Process" << endl;
}

void CCmdWindow::write_cmd()
{
    /* ������\r\n������̵�Enter��û���򲻻�ִ�� */
    QString cmd = ui->lineEdit->text() + "\r\n";
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();

    CSystemPub::setCodecGBK();

    /* תΪchar*��д�� */
    QByteArray qbarr = cmd.toLocal8Bit();
    char *ch = qbarr.data();
    qint64 len = cmd.length();
    process->write(ch, len);

    /* ��Ϣ��� */
    qDebug() << "Success:write_cmd��" << cmd << endl;
}

void CCmdWindow::read_data()
{
    CSystemPub::setCodecGBK();
    /* �������� */
    QByteArray bytes = process->readAll();

    /* ��ʾ */
    QString msg = QString::fromLocal8Bit(bytes);
    ui->textEdit->append(msg);
    ui->textEdit->update();

    /* ��Ϣ��� */
    qDebug() << "Success:read_data:" << msg << endl;

}

void CCmdWindow::finished_process()
{
    /* �������� */
    int flag = process->exitCode();

    /* ��Ϣ��� */
    qDebug() << "Success:finishedProcess():" << flag << endl;
}

void CCmdWindow::error_process()
{
    /* �������� */
    int err_code  = process->exitCode();
    QString err = process->errorString();

    /* ��ʾ */
    ui->textEdit->append(QString("error coed:%1").arg(err_code));
    ui->textEdit->append(err);

    /* ��Ϣ��� */
    qDebug() << "Success:error_process():" << err << endl;
}
