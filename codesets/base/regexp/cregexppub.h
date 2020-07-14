#ifndef CREGEXPPUB_H
#define CREGEXPPUB_H


#include <QRegExp>
#include <QRegularExpression>
#include "basetypepub.h"
#include "cfilepub.h"

typedef QString (*handlerRegExp)(QString text,QStringList regbefore, QStringList regafter);
typedef QString (*handlerTip)(QString configfilename, quint32 dwClasstype);
typedef QString (*handlerPost)(QString text);

typedef struct T_GenCode{
    WORD32 dwClasstype;    /* 类型 */
    QString filename ;    /* 文件名称 */
    handlerRegExp m_handler ;    /* 回调函数 */
    handlerTip    m_tip ;    /* 帮忙，提示 */
    handlerPost   m_handler_post ;    /* 回调后函数 */
}T_GenCode, *P_GenCode;


enum EUM_CLASSTYPE{
    CONSTRUCTOR,
    DESTRUCTOR,
    GETTER,
    SETTER,
    GETTER_AND_SETTER,
    EQUALITY_OPERATOR,
    RELATIONAL_OPERATOR,
    STREAM_OUTPUT_OPERATER,
    OVEERRIDE_FUNCTIONS,
    IMPLEMENT_FUNCTIONS,
    GENERATE_DEFINATION,
    COMMON_OPERATIONS, //公共使用
};



class CRegExpPub
{
public:
    CRegExpPub();
    static QString getRegExpFileNameBefore(QString filename);
    static QString getRegExpFileNameAfter(QString filename);
    static QString getRegExpFileNameTips(QString filename);
    static QString getRegExpByFile(QString filename);
    static QStringList getRegExpsByFile(QString filename);
    static QString getFileNameByClassType(quint32 dwClasstype);
    static QString procTextByRegExpList(QString classconfig, quint32 dwClasstype, QString text);
    static QString checkRegExpFile(QString classconfig, quint32 dwClasstype
                                   , QStringList &regexpsbef
                                   , QStringList &regexpsaft
                                   , QStringList &regexpstip
                                   );
    static QString replaceSignsPub(QString text);
    static QString replaceSeqPub(QString text, quint32 dwStartSeq, quint32 dwCount, QRegularExpressionMatch match);
    static QString handlerRegExp_Getter(QString text,QStringList regbefore, QStringList regafter);
    static QString handlerRegExp_Getter_Single(QString text,QStringList regbefore, QStringList regafter);
    static QString handlerTip_Getter(QString configfilename, quint32 dwClasstype);
    static QString handlerTip(QString classconfig, quint32 dwClasstype);
    static QString handlerPost_Common(QString text);
//    static QString handlerRegExp_Setter(QString text,QStringList regbefore, QStringList regafter);
//    static QString handlerTip_Setter();

    static const QString getConfigBefore();

private:
    static const QString dirbefore;
    static const QString dirafter;
    static const QString dirtips;
};





#endif // CREGEXPPUB_H
