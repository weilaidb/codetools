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

#endif // EXPRESSPUB_H
