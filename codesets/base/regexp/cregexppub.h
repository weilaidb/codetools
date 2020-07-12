#ifndef CREGEXPPUB_H
#define CREGEXPPUB_H


#include <QRegExp>
#include <QRegularExpression>
#include "basetypepub.h"
#include "cfilepub.h"

typedef QString (*handlerRegExp)(QString text,QStringList regbefore, QStringList regafter);
typedef QString (*handlerTip)();

typedef struct T_GenCode{
    WORD32 dwClasstype;    /* 类型 */
    QString filename ;    /* 文件名称 */
    handlerRegExp m_hander ;    /* 回调函数 */
    handlerTip    m_tip ;    /* 帮忙，提示 */
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
};



class CRegExpPub
{
public:
    CRegExpPub();
    static QString getRegExpFileNameBefore(QString filename);
    static QString getRegExpFileNameAfter(QString filename);
    static QString getRegExpByFile(QString filename);
    static QStringList getRegExpsByFile(QString filename);
    static QString getFileNameByClassType(quint32 dwClasstype);
    static QString procTextByRegExpList(quint32 classtype, QString text);
    static QString replaceSignsPub(QString text);
    static QString replaceSeqPub(QString text, quint32 dwStartSeq, quint32 dwCount, QRegularExpressionMatch match);
    static QString handlerRegExp_Getter(QString text,QStringList regbefore, QStringList regafter);
    static QString handlerRegExp_Getter_Single(QString text,QStringList regbefore, QStringList regafter);
    static QString handlerTip_Getter();
    static QString handlerTip(quint32 dwClasstype);
//    static QString handlerRegExp_Setter(QString text,QStringList regbefore, QStringList regafter);
//    static QString handlerTip_Setter();


private:
    static const QString dirbefore;
    static const QString dirafter;
};





#endif // CREGEXPPUB_H
