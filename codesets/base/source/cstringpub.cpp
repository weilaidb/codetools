#include "cstringpub.h"

#include <QStringList>

CStringPub::CStringPub()
{

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
