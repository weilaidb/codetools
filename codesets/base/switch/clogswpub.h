#ifndef CLOGSWPUB_H
#define CLOGSWPUB_H

#ifndef ARRAYSIZE
#define ARRAYSIZE(A) ((unsigned int)(sizeof(A)/sizeof(A[0])))
#endif


#define SIGMEB(VAL, NAME)  {#NAME, VAL},

enum E_LogSw{
    INDEX_LOGSW_TEST_1,
    INDEX_LOGSW_TEST_2,

    INDEX_LOGSW_MAX,
};


#define MULTI_LOGSW_ITEMS \
{\
    SIGMEB(0,INDEX_LOGSW_TEST_1)   \
    SIGMEB(0,INDEX_LOGSW_TEST_2)   \
};



typedef struct T_LogSw {
    const char *mName;           /* 名称 */
    unsigned int mVal;     /* 值 */
}T_LogSw, *P_LogSw;



class CLogSwPub
{
public:
    CLogSwPub();

    static unsigned int diagGetLogSw (unsigned int dwIndex);
    static unsigned int diagSetLogSw (unsigned int dwIndex, unsigned int dwVal);
    static unsigned int diagShowLogSw ();
};

#ifdef __cplusplus
extern "C" {
#endif

unsigned int diagGetLogSw (unsigned int dwIndex);
unsigned int diagSetLogSw (unsigned int dwIndex, unsigned int dwVal);
unsigned int diagShowLogSw ();

#ifdef __cplusplus
}
#endif


#endif // CLOGSWPUB_H


