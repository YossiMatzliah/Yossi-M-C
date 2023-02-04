/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		31/01/2023		*
*	Reviewer:	Noam			*
********************************/

#include <assert.h> /* assert */

#include "/home/yossi/git/ds/include/bit_array.h"

bit_array_t BitArraySetOn(bit_array_t bit_arr, size_t index)
{
	bit_array_t index_tmp = (size_t)1 << index;
	
	assert( BIT_ARRAY_SIZE > index );
	
	return (bit_arr | index_tmp);
}

bit_array_t BitArraySetOff(bit_array_t bit_arr, size_t index)
{
	bit_array_t index_tmp = ~((size_t)1 << index);
	
	assert( BIT_ARRAY_SIZE > index );
	
	return (bit_arr & index_tmp);

}

bit_array_t BitArraySetVal(bit_array_t bit_arr, size_t index, int bool_value)
{
	assert(0 == bool_value || 1 == bool_value);
	assert( BIT_ARRAY_SIZE > index );
	
	if (0 != bool_value)
	{
		return BitArraySetOn(bit_arr, index);
	}
	
	return BitArraySetOff(bit_arr, index);

}

bit_array_t BitArraySetAll(bit_array_t bit_arr)
{
	(void)bit_arr;
	return ~0;								
}

bit_array_t BitArrayResetAll(bit_array_t bit_arr)
{
	(void)bit_arr;
	return 0;
}

bit_array_t BitArrayFlip(bit_array_t bit_arr, size_t index)
{
	bit_array_t index_tmp = (size_t)1 << index;
	
	assert( BIT_ARRAY_SIZE >= index );
	
	return (bit_arr ^ index_tmp);
}

bit_array_t BitArrayMirror(bit_array_t bit_arr)
{
	bit_array_t mirror = 0;
    size_t i = 0;
	
    for(i = 0; BIT_ARRAY_SIZE > i; ++i)
    {
        mirror <<= 1;
        
        if(bit_arr & 1)
		{
			++mirror;
		}
		
		bit_arr >>= 1; 
	}
	return mirror;
}
		
bit_array_t BitArrayRotateLeft(bit_array_t bit_arr, size_t step)
{
	return bit_arr << step | (bit_arr >> (BIT_ARRAY_SIZE - step));
}

bit_array_t BitArrayRotateRight(bit_array_t bit_arr, size_t step)
{
	return BitArrayRotateLeft(bit_arr, -step);
}

size_t BitArrayCountOn(bit_array_t bit_arr)
{
	size_t count_on = 0;
	
	while (0 != bit_arr)
	{
		++count_on;  
		bit_arr &= (bit_arr - 1);
	}
	return count_on;
}

size_t BitArrayCountOff(bit_array_t bit_arr)
{
	return BitArrayCountOn(~bit_arr);
}

int BitArrayGet(bit_array_t bit_arr, size_t index)
{
	bit_array_t index_tmp = (size_t)1 << index;
	
	assert(BIT_ARRAY_SIZE >= index);
	
	return (0 != (bit_arr & index_tmp));
}

char *BitArrayToString(bit_array_t bit_arr, char *dest)
{
	int i = 0;
	for (i = 0; i < BIT_ARRAY_SIZE; ++i) 
	{
		dest[BIT_ARRAY_SIZE - i - 1] = (bit_arr & ((size_t)1 << i)) ? '1' : '0';
	}
	dest[BIT_ARRAY_SIZE] = '\0';
	
	return dest;

}
