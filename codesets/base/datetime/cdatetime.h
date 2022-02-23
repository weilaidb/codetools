#ifndef CDATETIME_H
#define CDATETIME_H

#include <QString>



class CDateTime
{
public:
    CDateTime();

    static QString format1();
    static QString format2();
    static qint64 getCurTime();
};

#endif // CDATETIME_H
