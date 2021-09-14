#ifndef CTHREADEXTPUB_H
#define CTHREADEXTPUB_H

#include <QThread>



class CThreadExtPub : public QThread
{
   Q_OBJECT
private:
   int    m_seq=0;          //掷骰子次数序号
   int    m_diceValue;      //骰子点数
   bool   m_Paused=true;    //暂停
   bool   m_stop=false;     //停止
protected:
   void   run();  //线程任务
public:
   CThreadExtPub();
   void   diceBegin();      //掷一次骰子
   void   dicePause();      //暂停
   void   stopThread();     //结束线程
signals:
   void   newValue(int seq,int diceValue); //产生新点数的信号
};

#endif // CTHREADEXTPUB_H
