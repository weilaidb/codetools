#ifndef CSQLPUB_H
#define CSQLPUB_H


#include <QSql>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "basetypepub.h"

class CSqlPub
{
public:
    CSqlPub();
    static WORD32 openDb(QString hostName, QString dbName, QString userName, QString passWord);
};

#endif // CSQLPUB_H
