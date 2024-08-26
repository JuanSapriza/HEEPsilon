#ifndef _CGRA_FUNCTION_H_
#define _CGRA_FUNCTION_H_

#include <stdio.h>
#include <math.h>


unsigned reversebits ( unsigned *input_ptr, unsigned *NumBits_ptr, unsigned *result_ptr )
{
    unsigned i, rev;

    unsigned index = *input_ptr;
    unsigned NumBits = *NumBits_ptr;

    #pragma CGRA
    for ( i=rev=0; i < NumBits; i++ )
    {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }
    // *index_ptr = index;
    // *NumBits_ptr = NumBits;
    *result_ptr = rev;

    return 0;
}

#endif // _CGRA_FUNCTION_H_