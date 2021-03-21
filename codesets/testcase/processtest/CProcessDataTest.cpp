#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/fcntl.h>
#include <assert.h>
#include "cprocessdata.h"



class CTest: public CBaseInterface
{
public:
    virtual ~CTest(){};


    int Init()
    {
        CProcessData::GetInstance()->RegIdFunction(1, (MsgAction)&CTest::ProcessData1);
        CProcessData::GetInstance()->RegIdFunction(2, (MsgAction)&CTest::ProcessData2);
        return 0;
    }


    int ProcessData1(int iId, void *pData, int iLen)
    {
        val = 1;
        cout <<" process cmd1, id: "<<iId<<", iLen: "<<iLen<<", val = "<<val++<<endl;
        return 0;
    }


    int ProcessData2(int iId, void *pData, int iLen)
    {
        cout <<" process cmd1, id: "<<iId<<", iLen: "<<iLen<<", val = "<<val++<<endl;
        return 0;
    }


private:
    int val;
};


#if 0
int main(int argc, char **argv)
{
    printf("hello world\n");
    CTest test;


    test.Init();


    CProcessData::GetInstance()->ProcessData(1, NULL, 2);
    CProcessData::GetInstance()->ProcessData(2, NULL, 3);

    return 0;
}

#endif
