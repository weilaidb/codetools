#include "cnumpub.h"

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
