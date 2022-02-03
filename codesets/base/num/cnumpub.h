#ifndef CNUMPUB_H
#define CNUMPUB_H

#include <QtCore>

class CNumPub
{
public:
    CNumPub();
    static int getBitStatus(quint64 dwwNum, int pos);
    static bool isNumZero(quint32 dwNum);
    static int string2num(QString str);
    static quint32 string2UInt(QString str);
    static int string2Int(QString str);
    static float string2Float(QString str);
};

#endif // CNUMPUB_H
