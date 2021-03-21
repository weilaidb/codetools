#include "cprocessdata.h"

CProcessData* CProcessData::m_pInstance = NULL;

CProcessData::CProcessData()
{

}

CProcessData::~CProcessData()
{

}

int CProcessData::RegIdFunction(int iID, MsgAction func)
{
    m_FucnMap[iID] = func;
    return 0;
}

int CProcessData::ProcessData(int iID, void *pData, int iDataLen)
{
    map<int, MsgAction>::iterator iter = m_FucnMap.find(iID);
    if ( iter != m_FucnMap.end() )
    {
        ((CBaseInterface*)this->*(iter->second))(iID, pData, iDataLen);
    }
    else
    {
        cout<<"in CProcessData::ProcessData, not  find id: "<<iID<<" process func!"<<endl;
    }

    return 0;
}

CProcessData* CProcessData::GetInstance()
{
    if ( m_pInstance == NULL )
    {
        m_pInstance = new CProcessData;
    }

    return m_pInstance;
}
