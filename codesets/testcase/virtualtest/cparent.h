#ifndef CPARENT_H
#define CPARENT_H

#include "cgrandmaster.h"

class CParent:public CGrandMaster
{
public:
    CParent();
    virtual void sleep();
//    void sleep();

    virtual void hello();
    void noherit();
};

#endif // CPARENT_H
