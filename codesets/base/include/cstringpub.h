#ifndef CSTRINGPUB_H
#define CSTRINGPUB_H

#include <QStringList>
#include <QAction>

//数组大小
#ifndef ARRAYSIZE
#define ARRAYSIZE(A) (unsigned int)(sizeof(A)/sizeof(A[0]))
#endif

//定义字符
#define STRING_SELF_MENU ("Generate")


class CStringPub
{
public:
    CStringPub();
    static QStringList toStringList(const QList<QByteArray> list);
    static QStringList toStringListOnly(QString single);
    static QString stringList2String(const QStringList list, const char *pSign);
    static QString stringList2StringEnter(const QStringList list);
    //return list by sign
    static QStringList stringSplit(const QString str , const char sign);
    //return list by \n
    static QStringList stringSplitbyNewLine(const QString str);
    //return list by \n, filter a line with nothing
    static QStringList stringSplitbyNewLineFilterEmpty(const QString str);
    static QStringList stringSplitbyNewLineFilterEmptyUnique(const QString str);
    static QString stringSplitFindText(const QString str , const char sign, QString signadd, QString findtext);
    static QStringList stringUniqueSort(QStringList recentfiles);
    static QStringList stringUnique(QStringList recentfiles);
    static QStringList stringUniqueSortReverse(QStringList recentfiles);
    static QString getOpenFileNamesFilter(QStringList filters, QString sign);
    //return stringlist, only one item
    static QStringList emptyStringList();
    //return stringlist, every item is ""
    static QStringList emptyStringListCount(int count);
    static QString emptyString();
    static QString errorListLenthNg();
    static QStringList actionNameList(QAction *action);
    static QStringList languageNameFilter();
    static QStringList wordNameFilter();
    static int strSimLen(QString str);
    static QString strSim(QString str);
    static void clearString(QString &str);
    static void setString(QString &str, QString val);
    static QString getString(QString &str);
    static void clearStringList(QStringList &list);
    static QString stringFilterEmpty(const QString str);


    //字符串
    static QString stringSelfMenu();
    static bool atStringList(QString str, QStringList list);
    static bool inStringList(QString str, QStringList list, Qt::CaseSensitivity cs);

    //version
    static void printDateTime();
    static QString getDateTime();
};

#endif // CSTRINGPUB_H
