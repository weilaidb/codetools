#ifndef CRETURNPUB_H
#define CRETURNPUB_H

#include <QString>

class CReturnPub
{
public:
    CReturnPub();

    static QString errorStd();
    static QString errorConfigFileNoExist();
};

#endif // CRETURNPUB_H
