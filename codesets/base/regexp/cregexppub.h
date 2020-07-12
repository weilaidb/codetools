#ifndef CREGEXPPUB_H
#define CREGEXPPUB_H


#include <QRegExp>
#include "basetypepub.h"
#include "cfilepub.h"



typedef struct T_GenCode{
    WORD32 dwClasstype;    /* 类型 */
    QString filename ;    /* 文件名称 */
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




private:
    static const QString dirbefore;
    static const QString dirafter;
};





#endif // CREGEXPPUB_H
