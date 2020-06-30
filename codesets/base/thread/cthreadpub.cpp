#include "cthreadpub.h"
#include "debugApp.h"

CThreadPub::CThreadPub(): QThread(nullptr)
  ,m_runCount(10)
{

}

CThreadPub::CThreadPub(QObject* par) : QThread(par)
,m_runCount(10)
{

}

CThreadPub::~CThreadPub()
{
    qDebug() << "CThreadPub::~CThreadPub()";
}

void CThreadPub::setSomething()
{
    msleep(500);
    QString str = QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
    emit message(str);
}

void CThreadPub::getSomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void CThreadPub::setRunCount(int count)
{
    m_runCount = count;
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void CThreadPub::run()
{
    int count = 0;
    QString str = QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId());
    emit message(str);
    while(1)
    {
        sleep(1);
        ++count;
        emit progress(((float)count / m_runCount) * 100);
        emit message(QString("CThreadPub::run times:%1").arg(count));
        doSomething();
//        debugApp() << "thread runing:" << count;
        if(m_runCount == count)
        {
            break;
        }
    }

//    debugApp() << "quit:" << count;
    exit();
//    quit();
}


void CThreadPub::doSomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

