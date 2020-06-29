#ifndef CSTRINGPUB_H
#define CSTRINGPUB_H

#include <QStringList>
#include <QAction>

class CStringPub
{
public:
    CStringPub();
    static QStringList toStringList(const QList<QByteArray> list);
    static QStringList toStringListOnly(QString single);
    static QString stringList2String(const QStringList list, const char *pSign);
    static QStringList stringSplit(const QString str , const char sign);
    static QString stringSplitFindText(const QString str , const char sign, QString signadd, QString findtext);
    static QStringList stringUniqueSort(QStringList recentfiles);
    static QStringList stringUniqueSortReverse(QStringList recentfiles);
    static QString getOpenFileNamesFilter(QStringList filters, QString sign);
    static QStringList emptyStringList();
    static QString emptyString();
    static QStringList actionNameList(QAction *action);
    static QStringList languageNameFilter();
    static QStringList wordNameFilter();
};

#endif // CSTRINGPUB_H
