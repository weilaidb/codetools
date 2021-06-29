#ifndef CDEFINEPUB_H
#define CDEFINEPUB_H

//一个整数和字符串
#define DEF_ITEM_INT_STR(item, handler,handertip,handerpost) {item, #item , handler ,handertip,handerpost}

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define WORD32MAX (unsigned int)(~0)
#define WORD16MAX (unsigned short)(~0)
#define BYTEMAX (unsigned char)(~0)

class CDefinePub
{
public:
    CDefinePub();
};

#endif // CDEFINEPUB_H
