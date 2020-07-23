#ifndef CLOGPUB_H
#define CLOGPUB_H

#include <QString>
#include <iostream>
#include <string>



class CLogPub
{
public:
    CLogPub();

    static void logDefault(QString info);
    static void msgDefault(QString info);
    static void msgDefault(char *pMsg);


private:
    static QString m_logDefaultFileName;

};

#endif // CLOGPUB_H
