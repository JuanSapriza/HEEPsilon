#ifndef _CGRA_FUNCTION_H_
#define _CGRA_FUNCTION_H_

#include <stdint.h>

#define TEST_LENGTH 10

int isqrt32(unsigned* in_ptr, int *result_ptr)
{
	int mask = 1<<14;

	int temp = 0;
	int result = *result_ptr;

	// if(*in_ptr < 0) return 0;
	while(mask)
	{
		temp = result | mask;
		if((((int)temp)*((int)temp)) <= ((int)(*in_ptr)))
			result = temp;
		mask >>= 1;
	}
	*result_ptr = result;
	return 0;
}

#endif // _CGRA_FUNCTION_H_