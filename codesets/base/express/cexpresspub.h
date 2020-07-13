#ifndef CEXPRESSPUB_H
#define CEXPRESSPUB_H

/**
 * @brief The CExpressPub class
 * 变量的表达式
 */

class CExpressPub
{
public:
    CExpressPub();
    static bool isZero(int length);
    static bool isFull(int length);
    static bool isFalse(bool bok);
    static bool isTrue(bool bok);
    static bool isNullPtr(void *Ptr);
};

#endif // CEXPRESSPUB_H
