#include "regexppub.h"
#include "cstringpub.h"
#include "cexpresspub.h"
#include "creturnpub.h"

QString RegExpPub::dirbefore  = ("reg/before/");
QString RegExpPub::dirafter   = ("reg/after/");

RegExpPub::RegExpPub()
{

}

QString RegExpPub::getRegExpFileNameBefore(QString filename)
{
    return dirbefore.append(filename);
}

QString RegExpPub::getRegExpFileNameAfter(QString filename)
{
    return dirafter.append(filename);
}

QString RegExpPub::getRegExpByFile(QString filename)
{
    return  CFilePub::readFileAll(filename);
}

QStringList RegExpPub::getRegExpsByFile(QString filename)
{
    return  CStringPub::stringSplitbyNewLineFilterEmpty(getRegExpByFile(filename));
}

QString RegExpPub::procTextByRegExpList(QString filename, QString text)
{
    QString result("");
    QStringList regexpsbef = getRegExpsByFile(getRegExpFileNameBefore(filename));
    QStringList regexpsaft = getRegExpsByFile(getRegExpFileNameAfter(filename));
    if(CExpressPub::isZero(regexpsbef.length()))
    {
        return CReturnPub::strError();
    }

    if(CExpressPub::isZero(regexpsaft.length()))
    {
        regexpsaft = CStringPub::emptyStringListCount(regexpsbef.length());
    }

    if(regexpsbef.length() > regexpsaft.length())
    {
        regexpsaft.append(CStringPub::emptyStringListCount(regexpsbef.length() - regexpsaft.length()));
    }

    result = text;
    int dwLp = 0;
    foreach (QString item, regexpsbef) {
        result = result.replace(QRegExp(item), regexpsaft.at(dwLp));
        dwLp++;
    }

    return result;
}
