#ifndef CTHREADPUB_H
#define CTHREADPUB_H

#include <QThread>



class CThreadPub : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    CThreadPub();
    CThreadPub(QObject* par);
    ~CThreadPub();
    void setSomething();
    void getSomething();
    void setRunCount(int count);
    void run();
    void doSomething();
private:
    int m_runCount;
    char name[1024 * 1024];


};

#endif // CTHREADPUB_H
