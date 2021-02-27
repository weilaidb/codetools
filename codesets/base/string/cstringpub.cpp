#include "cstringpub.h"
#include "csignpub.h"
#include "debugApp.h"
#include <QStringList>
#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


CStringPub::CStringPub()
{

}

QStringList CStringPub::toStringListOnly(QString single)
{
    QStringList list;
    list.append(single);
    return list;
}

QStringList CStringPub::toStringList(const QList<QByteArray> list)
{
    QStringList strings;
    foreach (const QByteArray &item, list) {
        if(item.trimmed().isEmpty())
        {
            continue;
        }
        strings.append(QString::fromUtf8(item)); // Assuming local 8-bit.
    }
    return strings;
}

QString CStringPub::stringList2String(const QStringList list, const char *pSign)
{
    QString result("");
    foreach (QString item, list) {
        result += item + pSign;
    }

    return result;
}

QString CStringPub::stringList2StringEnter(const QStringList list)
{
    QString result("");
    foreach (QString item, list) {
        result += item + SIGNENTER;
    }

    return result;
}



QStringList CStringPub::stringSplit(const QString str , const char sign)
{
    return  str.split(sign);
}

QStringList CStringPub::stringSplitbyNewLine(const QString str)
{
    const char sign = '\n';
    return  str.split(sign);
}

QStringList CStringPub::stringSplitbyNewLineFilterEmpty(const QString str)
{
    QStringList result;
    const char sign = '\n';
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        result.append(item);
    }

    return result;
}

QStringList CStringPub::stringSplitbyNewLineFilterEmptyUnique(const QString str)
{
    QStringList result;
    const char sign = '\n';
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        //去除\r 空格等
        result.append(CStringPub::strSim(item));
    }

    result = CStringPub::stringUnique(result);
    return result;
}

QStringList CStringPub::stringSplitbyNewLineFilterEmptyUniqueSort(const QString str)
{
    QStringList result;
    const char sign = '\n';
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        //去除\r 空格等
        result.append(CStringPub::strSim(item));
    }

    result = CStringPub::stringUniqueSort(result);
    return result;
}


QString CStringPub::stringSplitFindText(const QString str , const char sign,QString signadd, QString findtext)
{
    QString result("");
    QStringList list = stringSplit(str, sign);
    foreach (QString item, list) {
        if(!item.contains(findtext))
        {
            continue;
        }
        result += item + signadd;
    }
    return result;
}

QStringList CStringPub::stringUnique(QStringList lists)
{
    lists.removeDuplicates();
    return lists;
}

void CStringPub::addStringUnique(QStringList &lists,QString str)
{
    lists.append(str);
    lists.removeDuplicates();
}

void CStringPub::addStringUniqueMax(QStringList &lists, QString str, int max)
{
    lists.append(str);
    lists.removeDuplicates();
    if(lists.count() > max)
    {
        lists.removeFirst();
    }
}

void CStringPub::addStringUniqueSortMax(QStringList &lists, QString str, int max)
{
    lists.append(str);
    lists.removeDuplicates();
    if(lists.count() > max)
    {
        lists.removeFirst();
    }
    lists.sort();
}


QStringList CStringPub::stringUniqueSort(QStringList lists)
{
    lists.sort();
    lists.removeDuplicates();
    return lists;
}

QStringList CStringPub::stringUniqueSortReverse(QStringList lists)
{
    QStringList reverse;
    reverse.clear();
    lists.sort();
    lists.removeDuplicates();

    QVector<QString> list = lists.toVector();
    QVectorIterator<QString> iterator(list);

    //从结尾开始逆向遍历
    while(iterator.hasPrevious()){
        reverse.append(iterator.previous());
    }

    return lists;
}

QString CStringPub::getOpenFileNamesFilter(QStringList filters, QString sign)
{
    QString result("");
    foreach (QString item, filters) {
        result += item + sign;
    }
    return result;
}


QStringList CStringPub::emptyStringList()
{
    QStringList list;
    list.clear();
    return list;
}

QStringList CStringPub::emptyStringListCount(int count)
{
    QStringList list;
    list.clear();
    int lp = 0;
    for(lp = 0; lp < count; lp++)
    {
        list.append("");
    }
    return list;
}

QString CStringPub::emptyString()
{
    return QString("");
}

QString CStringPub::stringRegExpBefore()
{
    return QString("(.*)");
}

QString CStringPub::stringRegExpAfter()
{
    return QString("\\1");
}


QString CStringPub::errorListLenthNg()
{
    return QString("error:列表长度不足");
}

QString CStringPub::errorRegExpInvalid()
{
    return QString("error:正则表达式异常，请认真检测");
}


QStringList CStringPub::actionNameList(QAction *action)
{
    QStringList autolist;
    autolist.append(action->iconText());
    debugApp() << "actionname:" << action->iconText();
    return autolist;
}


QStringList CStringPub::languageNameFilter()
{
    QStringList list;
    list << "*.c";
    list << "*.cpp";
    list << "*.cxx";
    list << "*.h";
    list << "*.hpp";
    list << "*.java";

    return list;
}

QStringList CStringPub::wordNameFilter()
{
    QStringList list;
    list << "*.doc";
    list << "*.docx";

    return list;
}


int CStringPub::strSimLen(QString str)
{
    return str.simplified().length();
}

QString CStringPub::strSim(QString str)
{
    return str.simplified();
}

QString CStringPub::stringSelfMenu()
{
    return STRING_SELF_MENU;
}

void CStringPub::clearString(QString &str)
{
    str.clear();
}

void CStringPub::setString(QString &str, QString val)
{
    str = val;
}

QString CStringPub::getString(QString &str)
{
    return str;
}

void CStringPub::clearStringList(QStringList &list)
{
    list.clear();
}


QString CStringPub::stringFilterEmpty(const QString str)
{
    QString result;
    const char sign = '\n';
    QStringList strlist = str.split(sign);
    foreach (QString item, strlist) {
        if(item.simplified().isEmpty())
        {
            continue;
        }
        result.append(item + sign);
    }

    return result;
}


bool CStringPub::atStringList(QString str, QStringList list)
{
    foreach (QString item, list) {
        if(CStringPub::strSim(item) == CStringPub::strSim(str))
        {
            return true;
        }
    }

    return false;
}

bool CStringPub::inStringList(QString str, QStringList list, Qt::CaseSensitivity cs)
{
    foreach (QString item, list) {
        if(item.contains(str, cs))
        {
            return true;
        }
    }

    return false;
}

void CStringPub::printDateTime()
{
    printf("Date : %s\n", __DATE__);
    printf("Time : %s\n", __TIME__);
    printf("File : %s\n", __FILE__);
    printf("Line : %d\n", __LINE__);
}


QString CStringPub::getDateTime()
{
    return QString("%1-%2").arg(__DATE__).arg(__TIME__);
}

QString CStringPub::hexToString(unsigned char *in, int len)
{
    int i = 0;
    unsigned char inChar,hi,lo;
    QString s;

    for (i=0; i<len; i++)
    {
        inChar = in[i];

        hi = (inChar & 0xF0) >> 4;
        if (hi > 9)
            hi = 'A' + (hi - 0x0A);
        else
            hi += 0x30;
        s.append(hi);

        lo = inChar & 0x0F;
        if (lo > 9)
            lo = 'A' + (lo - 0x0A);
        else
            lo += 0x30;
        s.append(lo);

        //        s.append(0x20);
    }

    return s;
}

QString CStringPub::hexToString(unsigned char *in)
{
    return hexToString(in,strlen((char *)in));
}

QString CStringPub::getCurrentExePath()
{
    //Qt 获取当前程序运行路径
    //获取程序当前运行目录
    QString fileName = QCoreApplication::applicationDirPath();
    return fileName;
}

bool CStringPub::contain(QString str, QString reg)
{
    return str.contains(QRegExp(reg));
}

string CStringPub::getDataOfStr(BYTE *pMsg, WORD32 dwLen)
{
    string res("");
    WORD32 dwLp = 0;
    CHAR buf[4];
    for(dwLp = 0; dwLp < dwLen; dwLp++)
    {
        snprintf(buf, sizeof(buf),"%02x", pMsg[dwLp]);
        res += buf;
    }

    return res;
}


