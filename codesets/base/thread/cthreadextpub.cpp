#include   "cthreadextpub.h"
#include   <QTime>
#include <QDebug>

CThreadExtPub::CThreadExtPub()
{//构造函数
}

void CThreadExtPub::setRunTime(int iRunTime)
{
    m_runtime = iRunTime;
}
void CThreadExtPub::diceBegin()
{ //开始掷骰子
    m_Paused=false;
}

void CThreadExtPub::dicePause()
{//暂停掷骰子
    m_Paused=true;
}

void CThreadExtPub::stopThread()
{//停止线程
    m_stop=true;
}

void CThreadExtPub::run()
{//线程任务
    int startSec = 0;
    int endSec = 0;
    QTime tTime;

    startSec = tTime.currentTime().second();
    m_stop=false;//启动线程时令m_stop=false
    m_seq=0; //掷骰子次数
    qsrand(QTime::currentTime().msec());//随机数初始化，qsrand是线程安全的
    while(!m_stop)//循环主体
    {
        if (!m_Paused)
        {

            m_diceValue=qrand(); //获取随机数
            m_diceValue=(m_diceValue % 6)+1;
            m_seq++;
            qDebug() << "in " << m_seq ;
            emit newValue(m_seq,m_diceValue);  //发射信号
        }
        qDebug() << "come here";
        msleep(500); //线程休眠500ms
        //超时后，退出
        endSec = tTime.currentTime().second();
//        qDebug() << "endSec:" << endSec;
//        qDebug() << "startSec:" << startSec;
//        qDebug() << "m_runtime:" << m_runtime;

        if(endSec - startSec > m_runtime)
        {
            break;
        }
    }
    quit();//相当于exit(0),退出线程的事件循环
}
