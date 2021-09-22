#ifndef CSYSTEMPUB_H
#define CSYSTEMPUB_H

#include <windows.h>

class CSystemPub
{
public:
    CSystemPub();

    static void execCmd(const char *command);
    static void setCodecGBK();
    static void setCodecUTF_8();
};

#endif // CSYSTEMPUB_H
