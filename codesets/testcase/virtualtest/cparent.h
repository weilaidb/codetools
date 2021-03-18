#ifndef CPARENT_H
#define CPARENT_H

#include "cgrandmaster.h"

class CParent:public CGrandMaster
{
public:
    CParent();
    virtual void sleep();
//    void sleep();

    void hello();
};

#endif // CPARENT_H
