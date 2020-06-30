#ifndef CSTRINGPUBCPP_H
#define CSTRINGPUBCPP_H

#include <iostream>
#include "cppbasetype.h"

using namespace std;
//普通，指定指针和长度
#define GETSTROFDATA(P,L) CStringPubCpp::getDataOfStr((BYTE *)P,L).c_str()
//结构体指针
#define GETSTROFDATAPTR(P) CStringPubCpp::getDataOfStr((BYTE *)P,sizeof(*P)).c_str()
//非指针变量
#define GETSTROFDATABUF(M) CStringPubCpp::getDataOfStr((BYTE *)&M,sizeof(M)).c_str()



class CStringPubCpp
{
public:
    CStringPubCpp();

    static string getDataOfStr(BYTE *pMsg, WORD32 dwLen);
};

#endif // CSTRINGPUBCPP_H
