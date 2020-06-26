#ifndef CARRAYPUB_H
#define CARRAYPUB_H

#include "basepub.h"
#include "filepub.h"

class CArrayPub
{
public:
    CArrayPub();

    static void printArray(char **argv, int size);

};

#endif // CARRAYPUB_H
