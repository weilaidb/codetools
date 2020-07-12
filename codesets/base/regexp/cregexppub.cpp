#include "cregexppub.h"
#include "cstringpub.h"
#include "cexpresspub.h"
#include "creturnpub.h"
#include "cdefinepub.h"

T_GenCode g_GenCode[] =
{
    DEF_ITEM_INT_STR(CONSTRUCTOR            ),
    DEF_ITEM_INT_STR(DESTRUCTOR             ),
    DEF_ITEM_INT_STR(GETTER                 ),
    DEF_ITEM_INT_STR(SETTER                 ),
    DEF_ITEM_INT_STR(GETTER_AND_SETTER      ),
    DEF_ITEM_INT_STR(EQUALITY_OPERATOR      ),
    DEF_ITEM_INT_STR(RELATIONAL_OPERATOR    ),
    DEF_ITEM_INT_STR(STREAM_OUTPUT_OPERATER ),
    DEF_ITEM_INT_STR(OVEERRIDE_FUNCTIONS    ),
    DEF_ITEM_INT_STR(IMPLEMENT_FUNCTIONS    ),
    DEF_ITEM_INT_STR(GENERATE_DEFINATION    ),
};

const QString CRegExpPub::dirbefore  = ("reg/before/");
const QString CRegExpPub::dirafter   = ("reg/after/");

CRegExpPub::CRegExpPub()
{

}

QString CRegExpPub::getRegExpFileNameBefore(QString filename)
{
    return dirbefore + (filename);
}

QString CRegExpPub::getRegExpFileNameAfter(QString filename)
{
    return dirafter  +  (filename);
}

QString CRegExpPub::getRegExpByFile(QString filename)
{
    //创建空文件如果文件不存在
    CFilePub::createFileNoExist(filename);
    return  CFilePub::readFileAll(filename);
}

QStringList CRegExpPub::getRegExpsByFile(QString filename)
{
    return  CStringPub::stringSplitbyNewLineFilterEmpty(getRegExpByFile(filename));
}

QString CRegExpPub::getFileNameByClassType(quint32 dwClasstype)
{
    quint32 dwLp = 0;
    for(dwLp = 0; dwLp < ARRAYSIZE(g_GenCode);dwLp++)
    {
        if(dwClasstype == g_GenCode[dwLp].dwClasstype)
        {
            return g_GenCode[dwLp].filename;
        }
    }
    return CStringPub::emptyString();
}

QString CRegExpPub::procTextByRegExpList(quint32 dwClasstype, QString text)
{
    QString result("");
    QString filename = getFileNameByClassType(dwClasstype);
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
