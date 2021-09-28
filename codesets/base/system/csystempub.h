#ifndef CSYSTEMPUB_H
#define CSYSTEMPUB_H

#include <QString>
#include <windows.h>
#include <QDebug>

#define MAX_LENGTH (2048 *2)

class CSystemPub
{
public:
    CSystemPub();

    static void execCmd(const char *command);
    static void execCmd(QString command);
    static void setCodecGBK();
    static void setCodecUTF_8();
    static QString getSystemEnvironment();
    static void explorer(const char *command);
    static void explorer(QString command);
    static char *convertQString2buf(QString single);

private:
    static char szLogin[MAX_LENGTH];
};

#endif // CSYSTEMPUB_H
