#ifndef _CGRA_FUNCTION_H_
#define _CGRA_FUNCTION_H_

#include <stdint.h>
#include <stdio.h>

# define GSM_ABS(a) ((a) < 0 ? ((a) == MIN_WORD ? MAX_WORD : -(a)) : (a))
#define MIN_WORD    ((-32767)-1)
#define MAX_WORD    ( 32767)

int gsm(int *dmax_ptr, int *d){

    int dmax = *dmax_ptr;
    int temp = 0;

    #pragma CGRA
    for (int k = 0; k <= 39; k++) {
        temp = d[k];
        temp = GSM_ABS( temp );
        if (temp > dmax) dmax = temp;
    }

    *dmax_ptr = dmax;

    return 0;
}



#endif // _CGRA_FUNCTION_H_