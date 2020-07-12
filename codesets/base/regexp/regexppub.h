#ifndef REGEXPPUB_H
#define REGEXPPUB_H


#include <QRegExp>
#include "basetypepub.h"
#include "cfilepub.h"

typedef struct T_GenCode{
    WORD32 dwRet;    /* 数据量变更 */
}T_GenCode, *P_GenCode;



class RegExpPub
{
public:
    RegExpPub();

    static QString getRegExpFileNameBefore(QString filename);
    static QString getRegExpFileNameAfter(QString filename);
    static QString getRegExpByFile(QString filename);
    static QStringList getRegExpsByFile(QString filename);
    static QString procTextByRegExpList(QString filename, QString text);



private:
    static QString dirbefore;
    static QString aftername;
};





#endif // REGEXPPUB_H
