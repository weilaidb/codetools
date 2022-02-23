#include "cnumpub.h"
#include "cdatetime.h"

quint32 CNumPub::m_sdwStaticNum = 0;

CNumPub::CNumPub()
{

}

int CNumPub::getBitStatus(quint64 dwwNum, int pos)
{
    if(dwwNum & (1 << pos)) //按位与之后的结果非0
    {
//        printf("该位上的值为1");
        return 1;
    }
    else
    {
//        printf("该位上的值为0");
        return 0;
    }
}

bool CNumPub::isNumZero(quint32 dwNum)
{
    return (0 == dwNum);
}

quint32 CNumPub::string2UInt(QString str)
{
    return str.toUInt();
}

int CNumPub::string2Int(QString str)
{
    return str.toInt();
}

float CNumPub::string2Float(QString str)
{
    return str.toFloat();
}

quint32 CNumPub::getDwStaticNum()
{
    return m_sdwStaticNum;
}

quint32 CNumPub::getAddOneDwStaticNum(quint32 dwDefaultVal)
{
    static qint64 ls_oldtime = 0;
    static qint64 ls_curtime = 0;
    ls_curtime = CDateTime::getCurTime();
    if(ls_curtime - ls_oldtime > 5)
    {
        ls_oldtime = ls_curtime;
        m_sdwStaticNum = dwDefaultVal;
    }
    m_sdwStaticNum++;
    return m_sdwStaticNum;
}

QString CNumPub::getAddOneDwStaticNumString(quint32 dwDefault)
{
    return QString("%1").arg(getAddOneDwStaticNum(dwDefault));
}

void CNumPub::setDwStaticNum(const quint32 &dwStaticNum)
{
    m_sdwStaticNum = dwStaticNum;
}
