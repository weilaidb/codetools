#include "cdataprocess.h"
#include "debugApp.h"

CDataProcess * CDataProcess::m_instance = 0;


CDataProcess::CDataProcess()
{
}

CDataProcess::~CDataProcess()
{
}

int CDataProcess::registProcHandle(string cmd,MsgProcFunc handle)
{
    map<string,MsgProcFunc>::iterator iter = devCmdActionMap.find(cmd);
    if ( iter ==  devCmdActionMap.end() )
    {
        devCmdActionMap[cmd] = handle;
        return 0;
    }
    else
    {
        printf("in %s, cmd: %s, alreay in the map\n", __FUNCTION__, cmd.c_str());
    }


    return 0;
}

int CDataProcess::processDataFunction(string cmd, const void *pData, int iDataLen)
{
    map<string,MsgProcFunc>::iterator iter = devCmdActionMap.find(cmd);
    if ( iter !=  devCmdActionMap.end() )
    {
        return iter->second(cmd,pData, iDataLen);
    }
    else
    {
        printf("in %s, not find cmd: %s func\n", __FUNCTION__, cmd.c_str());
    }

    return -1;
}

CDataProcess *CDataProcess::getInstance()
{
    if (0 == m_instance)
    {
        m_instance = new CDataProcess();
    }
    return m_instance;
}


int printHelpInfo(string cmd, const void  *pData, int dataLen)
{
    cout <<"-----------------------------------"<<endl;
    cout <<"help info:"<<endl;
    cout <<"help: print this info."<<endl;
    cout <<"ver : print this demo ver."<<endl;
    cout <<"test: process test class func cmd."<<endl;
    cout <<"q   : exit."<<endl;
    cout <<"-----------------------------------"<<endl;


    return 0;
}

int printVer(string cmd, const void  *pData, int dataLen)
{
    cout <<"in printVer, ver 1.0.0"<<endl;
    return 0;
}

class testDataProc
{
public:
    int TestDataProcFunc(string cmd, const void  *pData, int dataLen)
    {
        cout << "in testDataProc::TestDataProcFunc, process cmd "<<cmd<<endl;
        return 0;
    }
};


#if 0
int main(int argc, char **argv)
{
    cout << "main begin" << endl;
    debugApp() << "main begin...";

    //静态函数注册
    CDataProcess::getInstance()->registProcHandle("help", printHelpInfo); //注册help命令处理函数
    CDataProcess::getInstance()->registProcHandle("ver", printVer);         //注册版本ver命令处理函数


    //测试类成员函数注册
//    testDataProc testProcObj; //这个是注册一个函数对象，test命令
//    CDataProcess::getInstance()->registProcHandle("test",(&testDataProc::TestDataProcFunc, testProcObj, _1, _2, _3));


    char cInPutBuf[256] = {0};
    while ( true )
    {
//        printf("inPut cmd>: ");
//        cout << "inPut cmd>: ";
        debugApp() << "...inPut cmd>:";
        memset(cInPutBuf, 0, sizeof(cInPutBuf));
        cin.getline(cInPutBuf,sizeof(cInPutBuf));  //读取一个命令
//        cin.getline();
        debugApp() << "cInPutBuf:" << cInPutBuf;
        if (cInPutBuf[0] == 'q')
        {
            cout <<"Bye!"<<endl;
            debugApp() << "...Bye!";
            break;
        }
        _sleep(1000);
        CDataProcess::getInstance()->processDataFunction(cInPutBuf, NULL, 0);  //处理命令
    }

    return 0;
}

#endif
