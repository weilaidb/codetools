#ifndef CSWITCHPUB_H
#define CSWITCHPUB_H

#ifndef ARRAYSIZE
#define ARRAYSIZE(A) ((unsigned int)(sizeof(A)/sizeof(A[0])))
#endif


#define SIGMEB(VAL, NAME)  {#NAME, VAL},

enum E_DrvSw{
    INDEX_DRVSW_TEST_1,
    INDEX_DRVSW_TEST_2,

    INDEX_DRVSW_MAX,
};


#define MULTI_DRVSW_ITEMS \
{\
    SIGMEB(0,INDEX_DRVSW_TEST_1)   \
    SIGMEB(0,INDEX_DRVSW_TEST_2)   \
};



typedef struct T_DrvSw {
    const char *mName;           /* 名称 */
    unsigned int mVal;     /* 值 */
}T_DrvSw, *P_DrvSw;



class CSwitchPub
{
public:
    CSwitchPub();

    static unsigned int diagGetDrvSw (unsigned int dwIndex);
    static unsigned int diagSetDrvSw (unsigned int dwIndex, unsigned int dwVal);
    static unsigned int diagShowDrvSw ();
};

#ifdef __cplusplus
extern "C" {
#endif

unsigned int diagGetDrvSw (unsigned int dwIndex);
unsigned int diagSetDrvSw (unsigned int dwIndex, unsigned int dwVal);
unsigned int diagShowDrvSw ();

#ifdef __cplusplus
}
#endif


#endif // CSWITCHPUB_H
