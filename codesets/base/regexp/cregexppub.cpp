#include "cregexppub.h"
#include "cstringpub.h"
#include "cexpresspub.h"
#include "creturnpub.h"
#include "cdefinepub.h"
#include "debugApp.h"

T_GenCode g_GenCode[] =
{
    DEF_ITEM_INT_STR(CONSTRUCTOR            ,NULL,NULL),
    DEF_ITEM_INT_STR(DESTRUCTOR             ,NULL,NULL),
    DEF_ITEM_INT_STR(GETTER                 ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip_Getter),
    DEF_ITEM_INT_STR(SETTER                 ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip_Getter),
    DEF_ITEM_INT_STR(GETTER_AND_SETTER      ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip_Getter),
    DEF_ITEM_INT_STR(EQUALITY_OPERATOR      ,NULL,NULL),
    DEF_ITEM_INT_STR(RELATIONAL_OPERATOR    ,NULL,NULL),
    DEF_ITEM_INT_STR(STREAM_OUTPUT_OPERATER ,NULL,NULL),
    DEF_ITEM_INT_STR(OVEERRIDE_FUNCTIONS    ,NULL,NULL),
    DEF_ITEM_INT_STR(IMPLEMENT_FUNCTIONS    ,NULL,NULL),
    DEF_ITEM_INT_STR(GENERATE_DEFINATION    ,NULL,NULL),
    DEF_ITEM_INT_STR(COMMON_OPERATIONS      ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip_Common),
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

QString CRegExpPub::handlerTip(quint32 dwClasstype)
{
    quint32 dwLp = 0;
    for(dwLp = 0; dwLp < ARRAYSIZE(g_GenCode);dwLp++)
    {
        if(dwClasstype == g_GenCode[dwLp].dwClasstype)
        {
            return g_GenCode[dwLp].m_tip();
        }
    }
    return CStringPub::emptyString();
}


QString CRegExpPub::replaceSignsPub(QString text)
{
    return text.replace("\\n", "\n").replace("\\t", "    ").replace("\\", "");
}

QString CRegExpPub::replaceSeqPub(QString text, quint32 dwStartSeq, quint32 dwCount, QRegularExpressionMatch match)
{
    QString result(text);
    quint32 dwLp = 0;
    for(dwLp = dwStartSeq; dwLp < dwCount; dwLp++)
    {
        //内容替换
        result = result.replace(QString("\\%1").arg(dwLp), match.captured(dwLp));
    }

    result = replaceSignsPub(result);
    return result;
}

/**
 * @brief CRegExpPub::procTextByRegExpList
 * @param classconfig --配置为空时，才使用classType
 * @param dwClasstype
 * @param text
 * @return
 */
QString CRegExpPub::procTextByRegExpList(QString classconfig, quint32 dwClasstype, QString text)
{
    QString result("");
    QString filename  = CStringPub::emptyString();
    if(CExpressPub::isFull(CStringPub::strSim(classconfig).length()))
    {
        filename = CStringPub::strSim(classconfig);
    }
    else
    {
        filename = getFileNameByClassType(dwClasstype);
    }

    QStringList regexpsbef = getRegExpsByFile(getRegExpFileNameBefore(filename));
    QStringList regexpsaft = getRegExpsByFile(getRegExpFileNameAfter(filename));
    if(CExpressPub::isZero(regexpsbef.length()))
    {
        return CReturnPub::strConfigFileNoExist();
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

    quint32 dwLp = 0;
    for(dwLp = 0; dwLp < ARRAYSIZE(g_GenCode);dwLp++)
    {
        if(dwClasstype == g_GenCode[dwLp].dwClasstype)
        {
            return g_GenCode[dwLp].m_hander(text, regexpsbef, regexpsaft);
        }
    }

    return result;
}

QString CRegExpPub::handlerRegExp_Getter_Single(QString text, QStringList regbefore, QStringList regafter)
{

    QString result = regafter.at(0);
    debugApp() << "reg before:" << regbefore;
    debugApp() << "reg after :" << regafter;

    QRegularExpression regularExpression(regbefore.at(0));
    int index = 0;
    QRegularExpressionMatch match;
    do {
        match = regularExpression.match(text, index);
        if(match.hasMatch()) {
            index = match.capturedEnd();
            qDebug()<<"("<<match.capturedStart() <<","<<index<<") "<<match.captured(0);
        }
        else
            break;
    } while(index < text.length());

    debugApp() << "match.caput1:" << match.capturedTexts();

    if(match.capturedTexts().length() < 4)
    {
        return CStringPub::listLenthNg();
    }

    result = replaceSeqPub(result, 1, match.capturedTexts().length(), match);

    return result;
}

QString CRegExpPub::handlerRegExp_Getter(QString text,QStringList regbefore, QStringList regafter)
{
    QString result = CStringPub::emptyString();
    QStringList list = CStringPub::stringSplitbyNewLineFilterEmpty(text);
    foreach (QString item, list) {
        result += handlerRegExp_Getter_Single(item, regbefore, regafter);
    }
    return result;
}

QString CRegExpPub::handlerTip_Getter()
{
    return ("int abc;");
}

QString CRegExpPub::handlerTip_Common()
{
    return ("please input something");
}



