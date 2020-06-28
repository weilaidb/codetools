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
    static QString stringSplitFindText(const QString str , const char sign, QString findtext);
    static QStringList stringUniqueSort(QStringList recentfiles);
    static QStringList stringUniqueSortReverse(QStringList recentfiles);
    static QString getOpenFileNamesFilter(QStringList filters, QString sign);
};

#endif // CSTRINGPUB_H
