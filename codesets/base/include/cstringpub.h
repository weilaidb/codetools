#ifndef CSTRINGPUB_H
#define CSTRINGPUB_H

#include <QStringList>
#include <QAction>

//数组大小
#define ARRAYSIZE(A) (unsigned int)(sizeof(A)/sizeof(A[0]))

//定义字符
#define STRING_SELF_MENU ("自定义")


class CStringPub
{
public:
    CStringPub();
    static QStringList toStringList(const QList<QByteArray> list);
    static QStringList toStringListOnly(QString single);
    static QString stringList2String(const QStringList list, const char *pSign);
    //return list by sign
    static QStringList stringSplit(const QString str , const char sign);
    //return list by \n
    static QStringList stringSplitbyNewLine(const QString str);
    //return list by \n, filter a line with nothing
    static QStringList stringSplitbyNewLineFilterEmpty(const QString str);
    static QString stringSplitFindText(const QString str , const char sign, QString signadd, QString findtext);
    static QStringList stringUniqueSort(QStringList recentfiles);
    static QStringList stringUniqueSortReverse(QStringList recentfiles);
    static QString getOpenFileNamesFilter(QStringList filters, QString sign);
    //return stringlist, only one item
    static QStringList emptyStringList();
    //return stringlist, every item is ""
    static QStringList emptyStringListCount(quint32 dwCount);
    static QString emptyString();
    static QString listLenthNg();
    static QStringList actionNameList(QAction *action);
    static QStringList languageNameFilter();
    static QStringList wordNameFilter();
    static int strSimLen(QString str);


    //字符串
    static QString stringSelfMenu();
};

#endif // CSTRINGPUB_H
