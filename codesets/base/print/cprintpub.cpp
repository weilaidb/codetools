#include "cprintpub.h"
#include "debugApp.h"


#include "cprintpub.h"
#include <sys/fcntl.h>
#include <QtDebug>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;



QString CPrintPub::m_filename = "";

CPrintPub::CPrintPub()
{

}

void CPrintPub::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toUtf8();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
    default:
        strMsg = QString("Warning:");
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString strMessage = QString("DateTime:%5 Message:%1 File:%2  Line:%3  Function:%4")
            .arg(strDateTime).arg(context.file).arg(context.line).arg(context.function).arg(localMsg.constData());

    // 输出信息至文件中（读写、追加形式）
//    qDebug() << "filename:" << m_filename;
//    QFile file(m_filename.toUtf8().data());
    QFile file("asytle.log");
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}


void CPrintPub::printToFile(QString fileName)
{
    m_filename = fileName; //此处定义文件不好使
    // 安装消息处理程序
    qInstallMessageHandler(myMessageOutput);
}

void CPrintPub::canclePrintToFile()
{
    qInstallMessageHandler(nullptr);
}


void CPrintPub::printArray(char **argv, int size)
{
    int i = 0;
    for(i= 0; i < size; i++)
    {
        if(nullptr == argv[i])
        {
            continue;
        }
        cout <<"No:" << i << ", " << argv[i] << endl;
    }
}




void CPrintPub::printStringList(QStringList list)
{
    foreach (QString item, list) {
        debugApp() << item;
    }
}

void CPrintPub::printStringListTip(QStringList list, QString tip)
{
    ////debugApp() << "-----:[" <<tip << "] begin!";
    foreach (QString item, list) {
        ////debugApp() << item;
    }
    ////debugApp() << "-----:[" <<tip << "] end!";
}


void CPrintPub::printString(QString str)
{
    ////debugApp() << str;
}

void CPrintPub::printStringData(QString str)
{
    QByteArray byte = str.toLocal8Bit().data();

    char *ch = byte.data();
    unsigned int dwLp =  0;
    for(dwLp = 0;dwLp < strlen(ch);dwLp++)
    {
//        cout <<"No:" << dwLp << ", " << ch[dwLp] << ",";

//        printf("0X%X", (unsigned char)ch[dwLp]);
        printf("No:%-3u, 0X%X, %c", dwLp, (unsigned char)ch[dwLp], ch[dwLp]);
        cout << endl;
    }

    ////debugApp() << str;
}


void CPrintPub::printStringTip(QString str, QString tip)
{
    ////debugApp() << tip << " : " << str;
}
