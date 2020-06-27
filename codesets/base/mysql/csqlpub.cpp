#include "csqlpub.h"
#include "debugApp.h"

CSqlPub::CSqlPub()
{

}

WORD32 CSqlPub::openDb(QString hostName,QString dbName, QString userName, QString passWord)
{
    QSqlDatabase dbconn;
    dbconn = QSqlDatabase::addDatabase("QMYSQL");
    dbconn.setHostName(hostName);
    dbconn.setDatabaseName(dbName);
    dbconn.setUserName(userName);
    dbconn.setPassword(passWord);

    qDebug("database open status: %d\n", dbconn.open());

    QSqlError error = dbconn.lastError();
    debugApp() << error.text();

    dbconn.close();
    return 0;
}
