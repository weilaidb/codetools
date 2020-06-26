#include "cprintpub.h"
#include <sys/fcntl.h>
#include <QtDebug>
#include <QMutex>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <iostream>

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

    QByteArray localMsg = msg.toLocal8Bit();

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
//    QFile file(m_filename.toLocal8Bit().data());
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

