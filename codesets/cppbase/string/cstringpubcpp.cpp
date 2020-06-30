#include "cstringpubcpp.h"

CStringPubCpp::CStringPubCpp()
{

}

string CStringPubCpp::getDataOfStr(BYTE *pMsg, WORD32 dwLen)
{
    string res("");
    WORD32 dwLp = 0;
    CHAR buf[4];
    for(dwLp = 0; dwLp < dwLen; dwLp++)
    {
        snprintf(buf, sizeof(buf),"%02x", pMsg[dwLp]);
        res += buf;
    }

    return res;
}



