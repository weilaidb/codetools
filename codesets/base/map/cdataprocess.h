#ifndef CDATAPROCESS_H
#define CDATAPROCESS_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>

using namespace std;


//typedef boost::function<int(string,const void *, int)>  MsgProcFunc;

typedef int(*MsgProcFunc)(string,const void *, int);


class CDataProcess
{
private:
    map<string,MsgProcFunc > devCmdActionMap; //用于存储消息命令字与处理函数对象

protected:
    CDataProcess();
    ~CDataProcess();
    static CDataProcess *m_instance;

public:
    static CDataProcess *getInstance();
    int registProcHandle(string cmd, MsgProcFunc handle);       //注册消息处理函数对象
    int processDataFunction(string cmd, const void *pData, int iDataLen);//消息处理
};

#endif // CDATAPROCESS_H
