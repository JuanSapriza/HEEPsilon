#ifndef _CGRA_FUNCTION_H_
#define _CGRA_FUNCTION_H_

#include <stdint.h>
#include<stdio.h>
/* SHA f()-functions */

#define f1(x,y,z)   ((x & y) | (~x & z))
#define f2(x,y,z)   (x ^ y ^ z)
#define f3(x,y,z)   ((x & y) | (x & z) | (y & z))
#define f4(x,y,z)   (x ^ y ^ z)

/* SHA constants */

#define CONST1      0x5a827999L
#define CONST2      0x6ed9eba1L
#define CONST3      0x8f1bbcdcL
#define CONST4      0xca62c1d6L

/* 32-bit rotate */

#define ROT32(x,n)  ((x << n) | ((uint32_t)x >> (32 - n)))

#define FUNC(n,i)                       \
    temp = ROT32(A,5) + f##n(B,C,D) + E + W[i] + CONST##n;  \
    E = D; D = C; C = ROT32(B,30); B = A; A = temp



int32_t * sha1(int32_t W[20]){
    static int32_t res[5];
    int32_t temp=0;
    int32_t A=0;
    int32_t B=0;
    int32_t C=0;
    int32_t D=0;
    int32_t E=0;


    for (int i = 0; i < 20; ++i) {
        FUNC(1,i);
    }

    res[0] = A;
    res[1] = B;
    res[2] = C;
    res[3] = D;
    res[4] = E;

    return res;

}


#endif // _CGRA_FUNCTION_H_