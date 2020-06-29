#ifndef EXPRESSPUB_H
#define EXPRESSPUB_H

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



#endif // EXPRESSPUB_H
