#ifndef CSIGNPUB_H
#define CSIGNPUB_H

#include <QString>
#include "signpub.h"

class CSignPub
{
public:
    CSignPub();

    static QString signEnter();
    static const char *signEnterExt();
    static char signEnterS();
    static QString signEnterNL();
    static QString signRESpace();
    static char signLXie();
    static QString signFenHao();
    static char signFenHaoC();


};

#endif // CSIGNPUB_H
