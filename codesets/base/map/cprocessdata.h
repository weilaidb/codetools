#ifndef CPROCESSDATA_H
#define CPROCESSDATA_H

#include <map>
#include "cbaseinterface.h"


class CProcessData
{
protected:
    CProcessData();
    ~CProcessData();


public:
    int ProcessData(int iID, void *pData, int iDataLen);  //处理消息
    int RegIdFunction(int iID, MsgAction func);           //注册消息处理成员函数


public:
    static CProcessData* GetInstance();

private:
    map<int , MsgAction>m_FucnMap;  //用于存储消息id与处理函数的对应表·
    static CProcessData* m_pInstance;
};

#endif // CPROCESSDATA_H
