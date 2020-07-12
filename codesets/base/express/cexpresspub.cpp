#include "cexpresspub.h"

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


bool CExpressPub::isFalse(bool bok)
{
    return (false == bok);
}

bool CExpressPub::isTrue(bool bok)
{
    return (true == bok);
}
