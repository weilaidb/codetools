#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cswitchpub.h"

T_DrvSw g_DrvSw[INDEX_DRVSW_MAX] =
        MULTI_DRVSW_ITEMS;



CSwitchPub::CSwitchPub()
{

}

unsigned int CSwitchPub::diagGetDrvSw (unsigned int dwIndex)
{
    if(dwIndex >= INDEX_DRVSW_MAX)
    {
        return UINT_MAX;
    }

    return g_DrvSw[dwIndex].mVal;
}

unsigned int CSwitchPub::diagSetDrvSw (unsigned int dwIndex, unsigned int dwVal)
{
    if(dwIndex >= INDEX_DRVSW_MAX)
    {
        return UINT_MAX;
    }
    g_DrvSw[dwIndex].mVal  = dwVal;
    return g_DrvSw[dwIndex].mVal;
}


unsigned int CSwitchPub::diagShowDrvSw ()
{
    unsigned int dwLp =  0;

    printf("%-5s%-40s%-5s\n", "NO", "NAME", "VALUE");
    for(dwLp = 0;dwLp < ARRAYSIZE(g_DrvSw);dwLp++)
    {
        printf("%-5u%-40s%-5u\n", dwLp+1, g_DrvSw[dwLp].mName, g_DrvSw[dwLp].mVal);
    }

    return 0;
}

#ifdef __cplusplus
extern "C" {
#endif


unsigned int diagGetDrvSw (unsigned int dwIndex)
{
    return CSwitchPub::diagGetDrvSw(dwIndex);
}

unsigned int diagSetDrvSw (unsigned int dwIndex, unsigned int dwVal)
{
    return CSwitchPub::diagSetDrvSw(dwIndex, dwVal);
}

unsigned int diagShowDrvSw ()
{
    return CSwitchPub::diagShowDrvSw();
}

#ifdef __cplusplus
}
#endif


