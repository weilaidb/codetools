#ifndef CNETTHREADPUB_H
#define CNETTHREADPUB_H

#include <QThread>
#include "basetypepub.h"

class CNetThreadPub : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    CNetThreadPub();
    CNetThreadPub(handler_retint_nopara handler);
    CNetThreadPub(QObject* par);
    ~CNetThreadPub();
    void setSomething();
    void getSomething();
    void setRunCount(int count);
    void run();
    void runDefault();
    void doSomething();
private:
    int m_runCount;
    handler_retint_nopara m_hander;


};

#endif // CNETTHREADPUB_H
