#include "cexpresspub.h"

#include <csignpub.h>
#include <cstringpub.h>

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

bool CExpressPub::isEmpty(QString str)
{
    return (0 == str.trimmed().length());
}

bool CExpressPub::isFull(QString str)
{
    return (0 != str.trimmed().length());
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

bool CExpressPub::isOkPtr(void *Ptr)
{
    return (nullptr != Ptr);
}

bool CExpressPub::isIndexXieLine(QString path)
{
    return (-1 != path.lastIndexOf(CSignPub::signLXie()));
}

bool CExpressPub::isSame(QString str, QString other)
{
    return (CStringPub::strSim(str) == CStringPub::strSim(other));
}

bool CExpressPub::isIn(QString str, QString other)
{
    return (str.contains(other));
}

QString CExpressPub::errorStd()
{
    return STR_ERROR;
}

QString CExpressPub::errorConfigFileNoExist()
{
    return STR_ERROR_CFGFILE_NOEXIST;
}

