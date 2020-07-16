#include "cregexppub.h"
#include "cstringpub.h"
#include "cexpresspub.h"
#include "creturnpub.h"
#include "cdefinepub.h"
#include "debugApp.h"
#include "csignpub.h"
#include "cprintpub.h"

T_GenCode g_GenCode[] =
{
    DEF_ITEM_INT_STR(CONSTRUCTOR            ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(DESTRUCTOR             ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(GETTER                 ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip_Getter ,NULL),
    DEF_ITEM_INT_STR(SETTER                 ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip_Getter ,NULL),
    DEF_ITEM_INT_STR(GETTER_AND_SETTER      ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip_Getter ,NULL),
    DEF_ITEM_INT_STR(EQUALITY_OPERATOR      ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(RELATIONAL_OPERATOR    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(STREAM_OUTPUT_OPERATER ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(OVEERRIDE_FUNCTIONS    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(IMPLEMENT_FUNCTIONS    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(GENERATE_DEFINATION    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(COMMON_OPERATIONS      ,CRegExpPub::handlerRegExp_Getter, CRegExpPub::handlerTip, CRegExpPub::handlerPost_Common),
};

const QString CRegExpPub::dirbefore  = ("reg/before/");
const QString CRegExpPub::dirafter   = ("reg/after/");
const QString CRegExpPub::dirtips    = ("reg/tips/");

CRegExpPub::CRegExpPub()
{

}

QString CRegExpPub::getRegExpFileNameBefore(QString filename)
{
    return dirbefore + CStringPub::strSim(filename);
}

QString CRegExpPub::getRegExpFileNameAfter(QString filename)
{
    return dirafter  +  CStringPub::strSim(filename);
}

QString CRegExpPub::getRegExpFileNameTips(QString filename)
{
    return dirtips  +  CStringPub::strSim(filename) + ".tip";
}


QString CRegExpPub::getRegExpFileNamePub(QString filename, int filetype)
{
    switch (filetype) {
    case FILE_TIPS:
        return getRegExpFileNameTips(filename);
    case FILE_BEFORE:
        return getRegExpFileNameBefore(filename);
    case FILE_AFTER:
        return getRegExpFileNameAfter(filename);
    default:
        break;
    }
    return CStringPub::emptyString();
}

QString CRegExpPub::setRegExpByFile(QString filename, QString content)
{
    return  CFilePub::writeFileWR(filename, content);
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

QString CRegExpPub::handlerTip(QString classconfig, quint32 dwClasstype, int filetype = FILE_TIPS)
{
    quint32 dwLp = 0;

    if(CExpressPub::isFull(CStringPub::strSimLen(classconfig)))
    {
        QStringList regexpsbef = CStringPub::emptyStringList();
        QStringList regexpsaft = CStringPub::emptyStringList();
        QStringList regexpstip = CStringPub::emptyStringList();
        checkRegExpFile(classconfig, dwClasstype, regexpsbef, regexpsaft, regexpstip);

        return getRegExpByFile(getRegExpFileNamePub(classconfig, filetype));
    }
    for(dwLp = 0; dwLp < ARRAYSIZE(g_GenCode);dwLp++)
    {
        if(dwClasstype == g_GenCode[dwLp].dwClasstype)
        {
            return g_GenCode[dwLp].m_tip(classconfig, dwClasstype, filetype);
        }
    }
    return CStringPub::emptyString();
}

void CRegExpPub::handlerTipSave(QString classconfig, quint32 dwClasstype
                                , QString content , int filetype = FILE_TIPS)
{
//    quint32 dwLp = 0;
    Q_UNUSED(dwClasstype);

    if(CExpressPub::isFull(CStringPub::strSimLen(classconfig)))
    {
        setRegExpByFile(getRegExpFileNamePub(classconfig, filetype), content);
    }
////    for(dwLp = 0; dwLp < ARRAYSIZE(g_GenCode);dwLp++)
////    {
////        if(dwClasstype == g_GenCode[dwLp].dwClasstype)
////        {
////            return g_GenCode[dwLp].m_tip(classconfig, dwClasstype, filetype);
////        }
////    }
//    return CStringPub::emptyString();
}



/**
 * @brief CRegExpPub::handlerPost_Common
 * @param text
 * @return 回调后处理函数
 */
QString CRegExpPub::handlerPost_Common(QString text)
{
    QString result("");
    result = text.replace(CStringPub::errorListLenthNg(), CStringPub::emptyString());
//    result = CStringPub::stringList2StringEnter(CStringPub::stringSplitbyNewLineFilterEmpty(text));
    return result;
}


QString CRegExpPub::replaceSignsPub(QString text)
{
    return text.replace("$NL", "\n").replace("$TB", "    ");
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

    CPrintPub::printStringTip(result, "replaceSeqPub before");
    result = replaceSignsPub(result);
    CPrintPub::printStringTip(result, "replaceSeqPub after");
    return result;
}

QString CRegExpPub::checkRegExpFile(QString classconfig, quint32 dwClasstype
                                    , QStringList &regexpsbef
                                    , QStringList &regexpsaft
                                    , QStringList &regexpstip
                                    )
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

    regexpsbef = getRegExpsByFile(getRegExpFileNameBefore(filename));
    regexpsaft = getRegExpsByFile(getRegExpFileNameAfter(filename));
    regexpstip = getRegExpsByFile(getRegExpFileNameTips(filename));
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

    QStringList regexpsbef = CStringPub::emptyStringList();
    QStringList regexpsaft = CStringPub::emptyStringList();
    QStringList regexpstip = CStringPub::emptyStringList();
    checkRegExpFile(classconfig, dwClasstype, regexpsbef, regexpsaft, regexpstip);

    if(CExpressPub::isZero(regexpsbef.length()))
    {
        return CReturnPub::errorConfigFileNoExist();
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
            if(g_GenCode[dwLp].m_handler)
            {
                result =  g_GenCode[dwLp].m_handler(text, regexpsbef, regexpsaft);
            }

            if(g_GenCode[dwLp].m_handler_post)
            {
                result =  g_GenCode[dwLp].m_handler_post(result);
            }
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

    if(match.capturedTexts().length() < 2)
    {
        return CStringPub::errorListLenthNg();
    }

    result = replaceSeqPub(result, 1, match.capturedTexts().length(), match);

    return result;
}

QString CRegExpPub::handlerRegExp_Getter(QString text,QStringList regbefore, QStringList regafter)
{
    QString result = CStringPub::emptyString();
    QStringList list = CStringPub::stringSplitbyNewLineFilterEmpty(text);
    foreach (QString item, list) {
        result += handlerRegExp_Getter_Single(item, regbefore, regafter) + SIGNENTER;
    }
    return result;
}

QString CRegExpPub::handlerTip_Getter(QString configfilename, quint32 dwClasstype,int filetype)
{
    Q_UNUSED(configfilename);
    Q_UNUSED(dwClasstype);
    Q_UNUSED(filetype);
    return ("int abc;");
}



const QString CRegExpPub::getConfigBefore()
{
    QString path =  CFilePub::getCurrentPath() + dirbefore;
    debugApp() << "path:" << path;
    return path;
}
