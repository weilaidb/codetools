#ifndef CSYSTEMPUB_H
#define CSYSTEMPUB_H

#include <windows.h>

class CSystemPub
{
public:
    CSystemPub();

    static void execCmd(const char *command);
};

#endif // CSYSTEMPUB_H
