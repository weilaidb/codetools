#ifndef CEXPRESSPUB_H
#define CEXPRESSPUB_H

#include <QString>


#define STR_ERROR ("error")
#define STR_ERROR_CFGFILE_NOEXIST ("the config file or config not exist")


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

//检测非法指针
#define CHECK_NULLPOINTER_RETURN(ptr) \
do{  \
    if(nullptr == ptr) \
    { \
        return; \
    } \
}while(0)

#define CHECK_NULLPOINTER_RETURN_EMPTYSTR(ptr) \
    do{  \
    if(nullptr == ptr) \
{ \
    return ""; \
    } \
    }while(0)

#define CHECK_NULLPOINTER_RETURN_STR(ptr,str) \
    do{  \
    if(nullptr == ptr) \
{ \
    return str; \
    } \
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
    static bool isOkPtr(void *Ptr);
    static bool isIndexXieLine(QString path);
    static bool isSame(QString str, QString other);
    static bool isIn(QString str, QString other);
    static QString errorStd();
    static QString errorConfigFileNoExist();
};

#endif // CEXPRESSPUB_H
