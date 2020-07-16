#ifndef CEXPRESSPUB_H
#define CEXPRESSPUB_H

#include <QString>




#define UNSED(A) (void)A;
#define STRWORDS(A) #A
#define BINDSTRWORDS(A) #A,A
#define CHECKSIZEZERORETURN(list) \
do{  \
    if(0 == list.size()) \
    { \
        return; \
    } \
}while(0)


#define CHECKSIZEZERO_TIPS_RETURN(list, func, tips) \
do{  \
    if(0 == list.size()) \
    { \
        func(tips); \
        return; \
    } \
}while(0)


#define CHECKEMPTYRETURN(list) \
do{  \
    if(list.isEmpty()) \
    { \
        return; \
    } \
}while(0)

#define CHECKEMPTY_TIPS_RETURN(list, func, tips) \
do{  \
    if(list.isEmpty()) \
    { \
        func(tips); \
        return; \
    } \
}while(0)


#define CHECKFALSERETURN(ret) \
do{  \
    if(false == ret) \
    { \
        return; \
    } \
}while(0)

#define CHECKFALSE_TIPS_RETURN(ret, func, tips) \
do{  \
    if(false == ret) \
    { \
        func(tips); \
        return; \
    } \
}while(0)

#define CHECKNEWMEMRETURN(EXP) \
do{  \
    try{\
        EXP;\
    }catch( const std::bad_alloc& e ){\
        return;\
    }\
}while(0)


/**
 * @brief The CExpressPub class
 * 变量的表达式
 */

class CExpressPub
{
public:
    CExpressPub();
    static bool isZero(int length);
    static bool isEmpty(QString str);
    static bool isFull(QString str);
    static bool isFull(int length);
    static bool isFalse(bool bok);
    static bool isTrue(bool bok);
    static bool isNullPtr(void *Ptr);
    static bool isIndexXieLine(QString path);
};

#endif // CEXPRESSPUB_H
