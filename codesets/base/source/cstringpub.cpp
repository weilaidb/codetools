#include "cstringpub.h"
#include "signpub.h"
#include "debugApp.h"
#include <QStringList>

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
        strings.append(QString::fromLocal8Bit(item)); // Assuming local 8-bit.
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

QStringList CStringPub::stringUniqueSort(QStringList lists)
{
    lists.removeDuplicates();
    lists.sort();
    return lists;
}

QStringList CStringPub::stringUniqueSortReverse(QStringList lists)
{
    QStringList reverse;
    reverse.clear();
    lists.removeDuplicates();
    lists.sort();

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

QStringList CStringPub::emptyStringListCount(quint32 dwCount)
{
    QStringList list;
    list.clear();
    quint32 dwLp = 0;
    for(dwLp = 0; dwLp < dwCount; dwLp++)
    {
        list.append("");
    }
    return list;
}

QString CStringPub::emptyString()
{
    return QString("");
}

QString CStringPub::listLenthNg()
{
    return QString("列表长度不足");
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


QString CStringPub::stringSelfMenu()
{
    return STRING_SELF_MENU;
}
