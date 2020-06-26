#include "carraypub.h"
#include <iostream>

using namespace std;

CArrayPub::CArrayPub()
{

}

void CArrayPub::printArray(char argv[ARGVROWS][FILENAMEMAX])
{
    int i = 0;
    int j = 0;
    for(i= 0; i < ARGVROWS; i++)
    {
        if('\0' == argv[i][0])
        {
            continue;
        }
        cout <<"No:" << i << ", " << argv[i] << endl;
    }
}
