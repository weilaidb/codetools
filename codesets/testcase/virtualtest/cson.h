#ifndef CSON_H
#define CSON_H

#include "cparent.h"
//class CParent;

class CSon:public CParent
{
public:
    CSon();
    virtual void sleep();
    virtual void hello();

    virtual void iamson();
    void noherit();
};

#endif // CSON_H
