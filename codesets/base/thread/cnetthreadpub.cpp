#include "cnetthreadpub.h"
#include "debugApp.h"


CNetThreadPub::CNetThreadPub(): QThread(nullptr)
  ,m_runCount(10)
  ,m_hander(nullptr)
{

}

CNetThreadPub::CNetThreadPub(handler_retint_nopara handler): QThread(nullptr)
  ,m_runCount(10)
  ,m_hander(handler)
{

}

CNetThreadPub::CNetThreadPub(QObject* par) : QThread(par)
  ,m_runCount(10)
  ,m_hander(nullptr)
{

}

CNetThreadPub::~CNetThreadPub()
{
    qDebug() << "CNetThreadPub::~CNetThreadPub()";
}

void CNetThreadPub::setSomething()
{
    msleep(500);
    QString str = QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
    emit message(str);
}

void CNetThreadPub::getSomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void CNetThreadPub::setRunCount(int count)
{
    m_runCount = count;
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void CNetThreadPub::run()
{
    if(m_hander)
    {
        m_hander();
    }
    else
    {
        runDefault();
    }

}


void CNetThreadPub::runDefault()
{
    int count = 0;
    QString str = QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg((int)QThread::currentThreadId());
    emit message(str);
    while(1)
    {
        sleep(1);
        ++count;
        emit progress(((float)count / m_runCount) * 100);
        emit message(QString("CNetThreadPub::run times:%1").arg(count));
        doSomething();
        //        debugApp() << "thread runing:" << count;
        if(m_runCount == count)
        {
            break;
        }
    }
}

void CNetThreadPub::doSomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

