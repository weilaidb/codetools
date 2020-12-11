#include "cregexppub.h"
#include "cstringpub.h"
#include "cexpresspub.h"
#include "cdefinepub.h"
#include "debugApp.h"
#include "csignpub.h"
#include "cprintpub.h"
#include "cmappub.h"
#include "basepub.h"

#include <QDateTime>
#include <cmappub.h>

T_GenCode g_GenCode[] =
{
    DEF_ITEM_INT_STR(CONSTRUCTOR            ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(DESTRUCTOR             ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(GETTER                 ,CRegExpPub::handlerRegExp_Pub, CRegExpPub::handlerTip_Getter ,NULL),
    DEF_ITEM_INT_STR(SETTER                 ,CRegExpPub::handlerRegExp_Pub, CRegExpPub::handlerTip_Getter ,NULL),
    DEF_ITEM_INT_STR(GETTER_AND_SETTER      ,CRegExpPub::handlerRegExp_Pub, CRegExpPub::handlerTip_Getter ,NULL),
    DEF_ITEM_INT_STR(EQUALITY_OPERATOR      ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(RELATIONAL_OPERATOR    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(STREAM_OUTPUT_OPERATER ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(OVEERRIDE_FUNCTIONS    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(IMPLEMENT_FUNCTIONS    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(GENERATE_DEFINATION    ,NULL,NULL,NULL),
    DEF_ITEM_INT_STR(COMMON_OPERATIONS      ,CRegExpPub::handlerRegExp_Pub, CRegExpPub::handlerTip, CRegExpPub::handlerPost_Pub),
};

//进制转换
T_SignPub g_ScaleSignPub[] =
{
    {SIGN_CUSTOM_H2D, "\\s*[0-9a-fA-F]+\\s*"},
    {SIGN_CUSTOM_D2H, "\\s*\\d+\\s*"},

    {SIGN_CUSTOM_H2B, "\\s*[0-9a-fA-F]+\\s*"},
    {SIGN_CUSTOM_B2H, "\\s*[0-1]+\\s*"},

    {SIGN_CUSTOM_D2B, "\\s*[0-9]+\\s*"},
    {SIGN_CUSTOM_B2D, "\\s*[0-1]+\\s*"},

    {SIGN_CUSTOM_UPP, "[\\w\\s]+"},
    {SIGN_CUSTOM_LOW, "[\\w\\s]+"},

//    {SIGN_CUSTOM_0XDOT, "\\w{2}+"},
};

const QString CRegExpPub::dirbase    = ("reg/");
const QString CRegExpPub::dirbefore  = ("reg/before/");
const QString CRegExpPub::dirafter   = ("reg/after/");
const QString CRegExpPub::dirtips    = ("reg/tips/");

CRegExpPub::CRegExpPub()
{

}



QString CRegExpPub::getFileSuffix(QString filename)
{
    //改名为.txt结尾的名称
    return filename + ".txt";
}

QString CRegExpPub::getRenameFile(QString filename)
{
    QFile file(filename);
    if(file.exists())
    {
        file.rename(getFileSuffix(filename));
    }
    file.close();

    return getFileSuffix(filename);
}

QString CRegExpPub::getRegExpFileNameBefore(QString filename)
{
    return getRenameFile(dirbefore + CStringPub::strSim(filename));
}

QString CRegExpPub::getRegExpFileNameAfter(QString filename)
{
    return getRenameFile(dirafter  +  CStringPub::strSim(filename));
}

QString CRegExpPub::getRegExpFileNameTips(QString filename)
{
    return getRenameFile(dirtips  +  CStringPub::strSim(filename) + ".tip");
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
    return  CFilePub::writeFileWOnly(filename, content);
}

QString CRegExpPub::getRegExpByFile(QString filename,QString content)
{
    //创建空文件如果文件不存在
    CFilePub::createFileContentNoExist(filename, content);
    return  CFilePub::readFileAll(filename);
}

QStringList CRegExpPub::getRegExpsByFile(QString filename,QString content)
{
    return  CStringPub::stringSplitbyNewLineFilterEmpty(getRegExpByFile(filename, content));
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
        QString regexpsmode    = CStringPub::emptyString();
        checkRegExpFile(classconfig, dwClasstype, regexpsbef, regexpsaft, regexpstip, regexpsmode);

        return getRegExpByFile(getRegExpFileNamePub(classconfig, filetype), CStringPub::emptyString());
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
    Q_UNUSED(dwClasstype);

    if(CExpressPub::isFull(CStringPub::strSimLen(classconfig)))
    {
        setRegExpByFile(getRegExpFileNamePub(classconfig, filetype), content);
    }
}



/**
 * @brief CRegExpPub::handlerPost_Pub
 * @param text
 * @return 回调后处理函数
 */
QString CRegExpPub::handlerPost_Pub(QString text)
{
    QString result("");
    result = text.replace(CStringPub::errorListLenthNg(), CStringPub::emptyString());
    //    result = CStringPub::stringList2StringEnter(CStringPub::stringSplitbyNewLineFilterEmpty(text));
    return result;
}


QString CRegExpPub::replaceSignsPub(QString text)
{
    QDateTime curDateTime=QDateTime::currentDateTime();

    text = text.replace(SIGN_CUSTOM_NL, "\n")
            .replace(SIGN_CUSTOM_TB, "    ")
            .replace(SIGN_CUSTOM_SP, " ")
            .replace(SIGN_CUSTOM_DATEX, curDateTime.toString("yyyy-MM-dd_hhmmss"))
            .replace(SIGN_CUSTOM_DATE, curDateTime.toString("yyyy-MM-dd hh:mm:ss"))
            ;

    text = replaceSignsItemPub(text);
//    replaceSignsItemTestPub(text);
    return text;
}

//按函数处理
//g_ScaleSignPub
QString CRegExpPub::replaceSignsItemFuncPub(QString dealText, P_SignPub temp)
{
    CHECK_NULLPOINTER_RETURN_STR(temp, dealText);
    g_ScaleSignPub;
    if(QString(SIGN_CUSTOM_H2D) == QString(temp->m_funname))
    {
        //十六进制转十进制
        dealText = CStringPub::scaleConvertPub(dealText, 16, 10);
    }
    else if(QString(SIGN_CUSTOM_D2H) == QString(temp->m_funname))
    {
        //十进制转十六进制
        dealText = CStringPub::scaleConvertPub(dealText, 10, 16);
    }

    else if(QString(SIGN_CUSTOM_H2B) == QString(temp->m_funname))
    {
        //十六进制转二进制
        dealText = CStringPub::scaleConvertPub(dealText, 16, 2);
    }
    else if(QString(SIGN_CUSTOM_B2H) == QString(temp->m_funname))
    {
        //二进制转十六进制
        dealText = CStringPub::scaleConvertPub(dealText, 2, 16);
    }
    else if(QString(SIGN_CUSTOM_D2B) == QString(temp->m_funname))
    {
        //十进制转二进制
        dealText = CStringPub::scaleConvertPub(dealText, 10, 2);
    }
    else if(QString(SIGN_CUSTOM_B2D) == QString(temp->m_funname))
    {
        //二进制转十进制
        dealText = CStringPub::scaleConvertPub(dealText, 2, 10);
    }
    else if(QString(SIGN_CUSTOM_UPP) == QString(temp->m_funname))
    {
        dealText = CStringPub::toUpper(dealText);
    }
    else if(QString(SIGN_CUSTOM_LOW) == QString(temp->m_funname))
    {
        dealText = CStringPub::toLower(dealText);
    }
//    else if(QString(SIGN_CUSTOM_0XDOT) == QString(temp->m_funname))
//    {
//        dealText = CStringPub::add0xDot(dealText);
//    }

    return dealText;
}

//特殊符号处理，比如进制转换，大小写等
QString CRegExpPub::replaceSignsItemPub(QString text)
{
    debugApp() << "bftext:" << text;

    //处理进制转换
    P_SignPub temp = NULL;
    QString filterstr("");
    WORD32 dwLp =  0;
    for(dwLp = 0;dwLp < ARRAYSIZE(g_ScaleSignPub);dwLp++)
    {
        temp = &g_ScaleSignPub[dwLp];
        filterstr = QString("\\%1\\(%2\\)").arg(temp->m_funname).arg(temp->m_filterregexp);
        debugApp() << "filterstr:" << filterstr;
        QRegularExpression regularExpression(filterstr, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
        int index = 0;
        QRegularExpressionMatch match;
        do {
            match = regularExpression.match(text, index);
            if(match.hasMatch()) {
                index = match.capturedEnd();
                debugApp()<<"("<<match.capturedStart() <<","<<index<<") "<<match.captured(0);
                QString dealText = match.captured(0);
                QString afText = dealText;
                afText = afText.replace(temp->m_funname,"").replace("(", "").replace(")","");
                debugApp() << "afText1:" << afText;
                afText = replaceSignsItemFuncPub(afText, temp);
                debugApp() << "afText2:" << afText;
                debugApp() << "dealText:" << dealText;
                debugApp() << "text1   :" << text;
                text = text.replace(dealText, afText);
                debugApp() << "text2   :" << text;
            }
            else
                break;
        } while(index < text.length());

        debugApp() << "match.caput1:" << match.capturedTexts();

        //        if(match.capturedTexts().length() < 2)
        //        {
        //            return CStringPub::errorListLenthNg();
        //        }


    }


    return text;
}

QString CRegExpPub::replaceSignsItemTestPub(QString text)
{
    debugApp() << "bftext:" << text;
    text = "$H2D(123)";
    /* 此处为何必须都加\\  */
    QString filterstr = ".*\\$H2D\\(\\d+\\).*";
    debugApp() << "bftext   :" << text;
    debugApp() << "filterstr:" << filterstr;

    QRegularExpression regularExpression(filterstr, QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption);
    int index = 0;
    QRegularExpressionMatch match;
    do {
        match = regularExpression.match(text, index);
        if(match.hasMatch()) {
            index = match.capturedEnd();
            debugApp()<<"("<<match.capturedStart() <<","<<index<<") "<<match.captured(0);
        }
        else
            break;
    } while(index < text.length());

    debugApp() << "match.caput1:" << match.capturedTexts();

    //        if(match.capturedTexts().length() < 2)
    //        {
    //            return CStringPub::errorListLenthNg();
    //        }

    return text;
}

QString CRegExpPub::replaceSeqMultiPub(QString text,QString regafter, int iStartSeq, int iCount, QRegularExpressionMatch match)
{
    QString result(text);
    int iLp = 0;
    for(iLp = iStartSeq; iLp <= iCount; iLp++)
    {
        //内容替换
        //        if(regafter.contains(QString("\\%1").arg(iLp)))
        //        {
        //            result = result.replace(QString("\\%1").arg(iLp), match.captured(iLp));
        //        }
        //        else
        {
            if(regafter.contains(SIGN_CUSTOM_SP))
            {
                regafter = regafter.replace(SIGN_CUSTOM_SP, " ");
            }
            QString toreplace = regafter;
            toreplace = toreplace.replace(QString("\\%1").arg(iStartSeq),match.captured(iLp));
//            debugApp() << ">>> in:";
//            debugApp() << "match.captured(iLp)  bf:" << match.captured(iLp);
//            debugApp() << "toreplace  bf:" << toreplace;
//            debugApp() << "result  bf:" << result;
            result = result.replace(match.captured(iLp),toreplace);
//            debugApp() << "result  af:" << result;
        }
    }

    CPrintPub::printStringTip(result, "replaceSeqMultiPub before");
    //    result = replaceSignsPub(result);
    CPrintPub::printStringTip(result, "replaceSeqMultiPub after");
    return result;
}

QString CRegExpPub::replaceSeqPub(QString text, int iStartSeq, int iCount, QRegularExpressionMatch match)
{
    QString result(text);
    int iLp = 0;
    for(iLp = iStartSeq; iLp < iCount; iLp++)
    {
        //内容替换
        result = result.replace(QString("\\%1").arg(iLp), match.captured(iLp));
    }

    CPrintPub::printStringTip(result, "replaceSeqPub before");
    result = replaceSignsPub(result);
    CPrintPub::printStringTip(result, "replaceSeqPub after");
    return result;
}

QString CRegExpPub::getFileNameByClassCfgType(QString classconfig, quint32 dwClasstype)
{
    QString filename  = CStringPub::emptyString();
    if(CExpressPub::isFull(CStringPub::strSim(classconfig).length()))
    {
        filename = CStringPub::strSim(classconfig);
    }
    else
    {
        filename = getFileNameByClassType(dwClasstype);
    }
    return filename;
}


QString CRegExpPub::checkRegExpFile(QString classconfig, quint32 dwClasstype
                                    , QStringList &regexpsbef
                                    , QStringList &regexpsaft
                                    , QStringList &regexpstip
                                    , QString &regexpmode
                                    )
{
    QString result("");
    QString filename  = getFileNameByClassCfgType(classconfig, dwClasstype);
    regexpsbef = getRegExpsByFile(getRegExpFileNameBefore(filename), CStringPub::stringRegExpBefore());
    regexpsaft = getRegExpsByFile(getRegExpFileNameAfter(filename), CStringPub::stringRegExpAfter());
    regexpstip = getRegExpsByFile(getRegExpFileNameTips(filename), CStringPub::emptyString());
    QMap<QString, QString> *pMap = CMapPub::getMapFileMode();
    if(pMap->end() != pMap->find(classconfig))
    {
        regexpmode = CMapPub::getMapFileMode()->find(classconfig).value();
    }
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
    QString regexpsmode    = CStringPub::emptyString();
    checkRegExpFile(classconfig, dwClasstype, regexpsbef, regexpsaft, regexpstip,regexpsmode);

    if(CExpressPub::isZero(regexpsbef.length()))
    {
        return CExpressPub::errorConfigFileNoExist();
    }

    if(CExpressPub::isZero(regexpsaft.length()))
    {
        regexpsaft = CStringPub::emptyStringListCount(regexpsbef.length());
    }

    if(regexpsbef.length() > regexpsaft.length())
    {
        regexpsaft.append(CStringPub::emptyStringListCount(regexpsbef.length() - regexpsaft.length()));
    }

    quint32 dwLp = 0;
    result = text;
    for(dwLp = 0; dwLp < ARRAYSIZE(g_GenCode);++dwLp)
    {
        if(dwClasstype == g_GenCode[dwLp].dwClasstype)
        {
            if(g_GenCode[dwLp].m_handler)
            {
                result =  g_GenCode[dwLp].m_handler(text, regexpsbef, regexpsaft, regexpsmode);
            }

            if(g_GenCode[dwLp].m_handler_post)
            {
                result =  g_GenCode[dwLp].m_handler_post(result);
            }
        }
    }

    return result;
}

QString CRegExpPub::handlerRegExp_Pub_Single(QString text, QStringList regbefore, QStringList regafter, QString mode)
{

    Q_UNUSED(mode);
    QString result = regafter.at(0);
    ////debugApp() << "reg before:" << regbefore;
    ////debugApp() << "reg after :" << regafter;

    QRegularExpression regularExpression(regbefore.at(0));
    int index = 0;
    QRegularExpressionMatch match;
    do {
        match = regularExpression.match(text, index);
        if(match.hasMatch()) {
            index = match.capturedEnd();
            ////debugApp()<<"("<<match.capturedStart() <<","<<index<<") "<<match.captured(0);
        }
        else
            break;
    } while(index < text.length());

    ////debugApp() << "match.caput1:" << match.capturedTexts();

    if(match.capturedTexts().length() < 2)
    {
        //        return CStringPub::errorListLenthNg();
        return result;
    }
    else
    {

    }

    result = replaceSeqPub(result, 1, match.capturedTexts().length(), match);

    return result;
}

QString CRegExpPub::handlerRegExp_Pub_MultiLine(QString text, QString regbefore, QString regafter, QString mode, QString &error)
{
    Q_UNUSED(mode);
    QString result = text;
    debugApp() << "reg before:" << regbefore;
    debugApp() << "reg after :" << regafter;

#if 1
    QRegularExpression regularExpression(regbefore
                                         , QRegularExpression::MultilineOption
                                         |QRegularExpression::DotMatchesEverythingOption
                                         |QRegularExpression::CaseInsensitiveOption
                                         );
    int index = 0;
    QRegularExpressionMatch match;
    quint32 dwMaxLoopCnt = 10000;
    do {
        match = regularExpression.match(text, index);
        if(match.hasMatch()) {
            index = match.capturedEnd();
//            debugApp()<<"("<<match.capturedStart() <<","<<index<<") "<<match.captured(0);
//            debugApp() << "match.capturedLength:" << match.capturedLength();
//            debugApp() << "match.capturedTexts.len :" << match.capturedTexts().length();
//            debugApp() << "match.capturedTexts :" << match.capturedTexts();
//            debugApp() << "match.capturedStart :" << match.capturedStart();
//            debugApp() << "match.capturedEnd   :" << match.capturedEnd();
//            debugApp() << "dwMaxLoopCnt        :" << dwMaxLoopCnt;
//            debugApp() << "reg after :" << regafter;
//            debugApp() << "result  bf:" << result;
//            debugApp() << "regularExpression.captureCount():" << regularExpression.captureCount();

            result = replaceSeqMultiPub(result, regafter, 1, regularExpression.captureCount(), match);
//            debugApp() << "result  af:" << result;
        }
        else
            break;
    } while(index < text.length() && --dwMaxLoopCnt);

    if(0 == dwMaxLoopCnt)
    {
        error = CStringPub::errorRegExpInvalid();
        return CStringPub::errorRegExpInvalid();
    }

//    debugApp() << "================lalst";
//    debugApp() << "match.capturedLength:" << match.capturedLength();
//    debugApp() << "match.capturedTexts.len :" << match.capturedTexts().length();
//    debugApp() << "match.capturedTexts :" << match.capturedTexts();
//    debugApp() << "match.capturedStart :" << match.capturedStart();
//    debugApp() << "match.capturedEnd   :" << match.capturedEnd();
//    debugApp() << "dwMaxLoopCnt        :" << dwMaxLoopCnt;

//    if(match.capturedTexts().length() < 2)
//    {
//        return CStringPub::errorListLenthNg();
//    }

//    result = replaceSeqMultiPub(result, regafter, 0, match.capturedTexts().length(), match);

#else
    QRegularExpression re(regbefore);
    /* 多行匹配 */
    re.setPatternOptions(QRegularExpression::MultilineOption);

    QString content(result);

    /* 全局匹配 */
    QRegularExpressionMatchIterator iter = re.globalMatch(content);

    int count = 0;
    /* 遍历查找匹配。 */
    while (iter.hasNext()) {
        QRegularExpressionMatch match = iter.next();
        /* 打印获取每次匹配到的结果 */
        ////debugApp() << "Index: " << QString::number(count)
                 << "Result: " << match.captured(0);

        QStringList capturedTexts = match.capturedTexts();
        /* 去除结果列表的第一个后得到组捕获列表。 */
        capturedTexts.removeFirst();

        ////debugApp() << "Index: " << QString::number(count)
                 << "Capture List: " << capturedTexts;
        result = result.replace(match.captured(0),regafter);
        count++;
    }

    if(0 == count)
    {
        ////debugApp() << "no matched";
    }
#endif

    return result;
}

QString CRegExpPub::handlerRegExp_Pub_Single(QString text, QString regbefore, QString regafter, QString mode)
{

    Q_UNUSED(mode);
    QString result = regafter;
    ////debugApp() << "reg before:" << regbefore;
    ////debugApp() << "reg after :" << regafter;

    QRegularExpression regularExpression(regbefore);
    int index = 0;
    QRegularExpressionMatch match;
    do {
        match = regularExpression.match(text, index);
        if(match.hasMatch()) {
            index = match.capturedEnd();
            ////debugApp()<<"("<<match.capturedStart() <<","<<index<<") "<<match.captured(0);
        }
        else
            break;
    } while(index < text.length());

    ////debugApp() << "match.caput1:" << match.capturedTexts();

    if(match.capturedTexts().length() < 2)
    {
        return CStringPub::errorListLenthNg();
    }

    result = replaceSeqPub(result, 1, match.capturedTexts().length(), match);

    return result;
}

QString CRegExpPub::handlerRegExp_Pub(QString text,QStringList regbefore, QStringList regafter, QString mode)
{
    QString result = CStringPub::emptyString();
    QString error = CStringPub::emptyString();
    QString strtmp = CStringPub::emptyString();
    QStringList list = CStringPub::stringSplitbyNewLineFilterEmpty(text);

    ////debugApp() << "mode:" << mode;
    //默认为一对一
    if(CExpressPub::isEmpty(mode))
    {
        foreach (QString item, list) {
            result += handlerRegExp_Pub_Single(item, regbefore.at(0), regafter.at(0), mode) + SIGNENTER;
        }
    }
    else if(mode == STR_MODE_SINGLELINE_EXECMULTI)
    {
        foreach (QString item, list) {
            quint32 dwLp = 0;
            strtmp = item;
            foreach (QString reg, regbefore) {
                strtmp = handlerRegExp_Pub_Single(strtmp, reg, regafter.at(dwLp), mode);
                dwLp++;
            }
            result += strtmp + SIGNENTER;
        }
    }
    else if(mode == STR_MODE_ALALLINE_EXECMULTI)
    {
        quint32 dwLp = 0;
        strtmp = text;

        //替换表达式替换处理一下，因为保存的内容是一行数据。
        QStringList toregafter = CStringPub::stringSplitbyNewLine(replaceSignsPub(regafter.at(0)));

        foreach (QString reg, regbefore) {
            strtmp = handlerRegExp_Pub_MultiLine(strtmp, reg, toregafter.at(dwLp), mode,error);
            if(CExpressPub::isFull(CStringPub::strSimLen(error)))
            {
                return error;
            }
            dwLp++;
        }
        debugApp() << "proc count:" << dwLp;
        result += strtmp + SIGNENTER;
    }

    return result;
}

QString CRegExpPub::handlerTip_Getter(QString configfilename, quint32 dwClasstype,int filetype)
{
    Q_UNUSED(configfilename)
    Q_UNUSED(dwClasstype)
    Q_UNUSED(filetype)
    return ("int abc;");
}

const QString CRegExpPub::getConfigBefore()
{
    QString path =  CFilePub::getCurrentPath() + dirbefore;
    ////debugApp() << "path:" << path;
    return path;
}

const QString CRegExpPub::getConfigBase()
{
    QString path =  CFilePub::getCurrentPath() + dirbase;
    ////debugApp() << "path:" << path;
    return path;
}

