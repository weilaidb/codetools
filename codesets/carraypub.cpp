#include "carraypub.h"
#include <iostream>

using namespace std;

CArrayPub::CArrayPub()
{

}

void CArrayPub::printArray(char **argv, int size)
{
    int i = 0;
    for(i= 0; i < size; i++)
    {
        if(nullptr == argv[i])
        {
            continue;
        }
        cout <<"No:" << i << ", " << argv[i] << endl;
    }
}
