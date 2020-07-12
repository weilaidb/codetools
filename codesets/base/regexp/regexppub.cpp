#include "regexppub.h"
#include "cstringpub.h"
#include "cexpresspub.h"

QString RegExpPub::beforename  = (".before.txt");
QString RegExpPub::aftername   = (".after.txt");

RegExpPub::RegExpPub()
{

}

QString RegExpPub::getRegExpFileNameBefore(QString filename)
{
    return filename.append(beforename);
}

QString RegExpPub::getRegExpFileNameAfter(QString filename)
{
    return filename.append(aftername);
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
    QStringList regexps = getRegExpsByFile(filename);
    if(CExpressPub::isZero(regexps.length()))
    {
        return result;
    }

    result = text;
    foreach (QString item, regexps) {
//        result = result.replace(QRegExp(item),);
    }


    return result;
}
