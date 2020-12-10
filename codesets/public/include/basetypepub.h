#ifndef BASETYPEPUB_H
#define BASETYPEPUB_H


typedef char CHAR;
typedef unsigned char BYTE;

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;


typedef unsigned short WORD;
typedef unsigned int   WORD32;
typedef unsigned long long WORD64;

//函数指针
typedef int (*handler_retint_nopara)(void);


#ifndef ARRAYSIZE
#define ARRAYSIZE(A) ((unsigned int)(sizeof(A)/sizeof(A[0])))
#endif



#endif // BASETYPEPUB_H
