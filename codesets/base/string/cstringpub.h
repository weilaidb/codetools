#ifndef CSTRINGPUB_H
#define CSTRINGPUB_H

#include <QStringList>
#include <QAction>
#include <iostream>
#include "basetypepub.h"

//定义字符
#define STRING_SELF_MENU ("Generate")

using namespace std;
//普通，指定指针和长度
#define GETSTROFDATA(P,L) CStringPubCpp::getDataOfStr((BYTE *)P,L).c_str()
//结构体指针
#define GETSTROFDATAPTR(P) CStringPubCpp::getDataOfStr((BYTE *)P,sizeof(*P)).c_str()
//非指针变量
#define GETSTROFDATABUF(M) CStringPubCpp::getDataOfStr((BYTE *)&M,sizeof(M)).c_str()


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
    static QStringList stringSplitbyNewLineTrimEnd(const QString str);
    static QStringList stringSplitbyNewLineTrimHeader(const QString str);
    static QStringList stringSplitbyNewLineTrimAll(const QString str);
    static QStringList stringSplitbyNewLineTrimEnd(const QStringList list);
    //return list by \n, filter a line with nothing
    static QStringList stringSplitbyCharFilterEmpty(const QString str, const char sign);
    static QStringList stringSplitbySpaceFilterEmpty(const QString str);
    static QStringList stringSplitbyNewLineFilterEmpty(const QString str);
    static QStringList stringSplitbyNewLineFilterEmptyUnique(const QString str);
    static QStringList stringSplitbyNewLineFilterEmptyUniqueSort(const QString str);
    static QString stringSplitFindText(const QString str , const char sign, QString signadd, QString findtext);
    static QStringList stringUniqueSort(QStringList recentfiles);
    static QStringList stringUnique(QStringList recentfiles);
    static QStringList reverseStringList (QStringList &lists);
    static void printStringList (QStringList &lists);
    static void addStringUnique(QStringList &lists, QString str);
    static void addStringUniqueMax(QStringList &lists, QString str, int max);
    static void addStringUniqueInverseMax(QStringList &lists, QString str, int max);
    static void addStringHeaderUniqueMax(QStringList &lists, QString str, int max);
    static void addStringUniqueSortMax(QStringList &lists, QString str, int max);
    static QStringList stringUniqueSortReverse(QStringList recentfiles);
    static QString getOpenFileNamesFilter(QStringList filters, QString sign);
    //return stringlist, only one item
    static QStringList emptyStringList();
    //return stringlist, every item is ""
    static QStringList emptyStringListCount(int count);
    static QString emptyString();
    static QString errorListLenthNg();
    static QString errorRegExpInvalid();
    static QString stringRegExpBefore();
    static QString stringRegExpAfter();
    static QStringList actionNameList(QAction *action);
    static QStringList languageNameFilter();
    static QStringList wordNameFilter();
    static unsigned int strSimLen(QString str);
    static bool strSimLenZero(QString str);
    static bool strSimLenFull(QString str);
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
    static QString getStringOfData(unsigned char *pStr, unsigned int dwLen, int hexflag);
    //replace
    static QString replaceReg(QString text, QString regexp, QString after);
    static QString replaceReg2Empty(QString text, QString regexp);
    static QString replaceRegLRKuohao2Empty(QString text);

    //version
    static void printDateTime();
    static QString getDateTime();

    static QString hexToString(unsigned char *in, int len);
    static QString hexToString(unsigned char *in);
    static QString getCurrentExePath();
    static bool contain(QString str, QString reg);

    //cpp string
    static string getDataOfStr(BYTE *pMsg, WORD32 dwLen);
    //filter list
    static QStringList filterFileListInclude(QString filter, QStringList list, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    static QStringList filterFileListNoInclude(QString filter, QStringList list, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    //查找关键字包括多个，以空格分隔
    static bool filterKeySpaceInclude(QString keySpace, QString orgtext, Qt::CaseSensitivity cs = Qt::CaseSensitive);

    //QDir
    static QString toNativeSeparators(QString dir);

    //进制转换
    static QString scaleConvertPub(QString text, quint8 from, quint8 to);
    static QString toUpper(QString text);
    static QString toLower(QString text);
    static QString add0xDot(QString text);
};

#endif // CSTRINGPUB_H
