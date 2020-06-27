#ifndef LOOPPUB_H
#define LOOPPUB_H

/**
  **循环执行EXPRESS
  **/
#define EXECLOOP(EXPRESS, NUMS) \
{\
    unsigned int dwLp = 0;\
    for(dwLp = 0; dwLp < NUMS;dwLp++)\
    {\
        EXPRESS;   \
    }\
}


#endif // LOOPPUB_H
