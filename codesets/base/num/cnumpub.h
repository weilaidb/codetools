#ifndef CNUMPUB_H
#define CNUMPUB_H

#include <QtCore>

class CNumPub
{
public:
    CNumPub();
    static int getBitStatus(quint64 dwwNum, int pos);
};

#endif // CNUMPUB_H
