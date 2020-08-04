#include "cstringpub.h"
#include "testcase.h"
#include "readmacro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef  struct
{
    int abc;
    int def;
    int ghk;
}T_test, *P_test;

#ifdef UT_TEST
#if READMACRO("单元测试")
int main(int argc, char *argv[])
{
    printf("testcase begin~~\n");
    T_test ts = {1,2,3};
    P_test ps = &ts;
    BYTE buf[20];
    memset(buf,'2',sizeof(buf));
    cout << CStringPubCpp::getDataOfStr(buf, sizeof(buf)) << endl;
    printf("%s\n", GETSTROFDATABUF(buf));
    printf("%s\n", GETSTROFDATA(buf, sizeof(buf)));
    printf("%s\n", GETSTROFDATAPTR(ps));
    printf("%s\n", GETSTROFDATABUF(ts));
    printf("testcase end~~\n");
    return 0;
}

#endif
#endif
