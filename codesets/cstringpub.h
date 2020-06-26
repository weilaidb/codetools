#ifndef CSTRINGPUB_H
#define CSTRINGPUB_H

#include <QStringList>

class CStringPub
{
public:
    CStringPub();
    static QStringList toStringList(const QList<QByteArray> list);
    static QString stringList2String(const QStringList list, const char *pSign);
    static QStringList stringSplit(const QString str , const char sign);
};

#endif // CSTRINGPUB_H
