#include "cexpresspub.h"

#include <csignpub.h>

CExpressPub::CExpressPub()
{

}

/**
 * @brief CExpressPub::isZero
 * @param length
 * @return TRUE if length zero
 */
bool CExpressPub::isZero(int length)
{
    return (0 == length);
}

bool CExpressPub::isZero(QString str)
{
    return (0 == str.simplified().length());
}

bool CExpressPub::isFull(int length)
{
    return (0 != length);
}


bool CExpressPub::isFalse(bool bok)
{
    return (false == bok);
}

bool CExpressPub::isTrue(bool bok)
{
    return (true == bok);
}


bool CExpressPub::isNullPtr(void *Ptr)
{
    return (nullptr == Ptr);
}

bool CExpressPub::isIndexXieLine(QString path)
{
    return (-1 != path.lastIndexOf(CSignPub::signLXie()));
}


