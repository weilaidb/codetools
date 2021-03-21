#ifndef CBASEINTERFACE_H
#define CBASEINTERFACE_H

#include <iostream>

using namespace std;

class CBaseInterface;

typedef int (CBaseInterface::*MsgAction)(int, void *, int);

class CBaseInterface
{
public:
    CBaseInterface(){};
    virtual ~CBaseInterface(){};

};

#endif // CBASEINTERFACE_H
