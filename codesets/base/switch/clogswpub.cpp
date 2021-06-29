



//////////////////////源文件
//////////////////////源文件
//////////////////////源文件
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "clogswpub.h"

T_LogSw g_LogSw[INDEX_LOGSW_MAX] =
        MULTI_LOGSW_ITEMS;



CLogSwPub::CLogSwPub()
{

}

unsigned int CLogSwPub::diagGetLogSw (unsigned int dwIndex)
{
    if(dwIndex >= INDEX_LOGSW_MAX)
    {
        return UINT_MAX;
    }

    return g_LogSw[dwIndex].mVal;
}

unsigned int CLogSwPub::diagSetLogSw (unsigned int dwIndex, unsigned int dwVal)
{
    if(dwIndex >= INDEX_LOGSW_MAX)
    {
        return UINT_MAX;
    }
    g_LogSw[dwIndex].mVal  = dwVal;
    return g_LogSw[dwIndex].mVal;
}


unsigned int CLogSwPub::diagShowLogSw ()
{
    unsigned int dwLp =  0;

    printf("%-5s%-40s%-5s\n", "NO", "NAME", "VALUE");
    for(dwLp = 0;dwLp < ARRAYSIZE(g_LogSw);dwLp++)
    {
        printf("%-5u%-40s%-5u\n", dwLp+1, g_LogSw[dwLp].mName, g_LogSw[dwLp].mVal);
    }

    return 0;
}

#ifdef __cplusplus
extern "C" {
#endif


unsigned int diagGetLogSw (unsigned int dwIndex)
{
    return CLogSwPub::diagGetLogSw(dwIndex);
}

unsigned int diagSetLogSw (unsigned int dwIndex, unsigned int dwVal)
{
    return CLogSwPub::diagSetLogSw(dwIndex, dwVal);
}

unsigned int diagShowLogSw ()
{
    return CLogSwPub::diagShowLogSw();
}

#ifdef __cplusplus
}
#endif







