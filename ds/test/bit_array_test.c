/********************************
*	Developper: Yossi Matzliah	*
*	Date: 		31/01/2023		*
*	Reviewer:	Noam			*
********************************/

#include "/home/yossi/git/ds/include/bit_array.h"

#define SET 1
#define OFF 0

void TestOne();
void TestTwo();
void LutCountOn();
void InitCountLut(size_t table[]);
size_t CountBitsLut(size_t n, size_t table[]); 
void InitMirrorTable(size_t mirror_table[]);
bit_array_t MirrorBitsLut(bit_array_t n, size_t mirror_table[]);

int main()
{
	TestOne();
	TestTwo();
	LutCountOn();
	
	return 0;
}

void TestOne()
{
	bit_array_t bit_arr = 123;
	size_t set_index = 2;
	size_t off_index = 3;
	size_t index = 0;
	size_t step = 0;
	char dest[64] = {OFF};
	
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArraySetOn(bit_arr, set_index);
	printf("BitArraySetOn index: %lu: %lu\n", set_index, bit_arr);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArraySetOff(bit_arr, off_index);
	printf("BitArraySetOn index: %lu: %lu\n", off_index, bit_arr);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	set_index = 7;
	off_index = 2;
	bit_arr = BitArraySetVal(bit_arr, set_index, SET);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArraySetVal(bit_arr, off_index, OFF);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	printf("The num of \"sets\" is: %lu\n", BitArrayCountOn(bit_arr));
	printf("The num of \"offs\" is: %lu\n", BitArrayCountOff(bit_arr));

	index = 2;
	printf("The value of index %lu is:"
	" %d\n", index, BitArrayGet(bit_arr, index));
	index = 5;
	printf("The value of index %lu is:"
	" %d\n", index, BitArrayGet(bit_arr, index));
	
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArrayFlip(bit_arr, index);
	printf("The value of index %lu ater flip is:"
	" %d\n", index, BitArrayGet(bit_arr, index));
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	bit_arr = BitArrayMirror(bit_arr);
	printf("After mirror the num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	step = 8;
	bit_arr = BitArrayRotateRight(bit_arr, step);
	printf("After rotate %lu times right, the num %lu represented to bit"
	" in a string is:\n%s\n", step, bit_arr, BitArrayToString(bit_arr, dest));
	
	step = 1;
	bit_arr = BitArrayRotateLeft(bit_arr, step);
	printf("After rotate %lu times right, the num %lu represented to bit"
	" in a string is:\n%s\n", step, bit_arr, BitArrayToString(bit_arr, dest));
	
	bit_arr = BitArraySetAll(bit_arr);
	printf("After SetAll the num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	bit_arr = BitArrayResetAll(bit_arr);
	printf("After ResetAll the num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
}

void TestTwo()
{
	bit_array_t bit_arr = 2354897132;
	size_t set_index = 4;
	size_t off_index = 7;
	size_t index = 0;
	size_t step = 0;
	char dest[64] = {OFF};
	
	printf("\n\nThe num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArraySetOn(bit_arr, set_index);
	printf("BitArraySetOn index: %lu: %lu\n", set_index, bit_arr);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArraySetOff(bit_arr, off_index);
	printf("BitArraySetOn index: %lu: %lu\n", off_index, bit_arr);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	set_index = 2;
	off_index = 4;
	bit_arr = BitArraySetVal(bit_arr, set_index, SET);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArraySetVal(bit_arr, off_index, OFF);
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	printf("The num of \"sets\" is: %lu\n", BitArrayCountOn(bit_arr));
	printf("The num of \"offs\" is: %lu\n", BitArrayCountOff(bit_arr));

	index = 2;
	printf("The value of index %lu is:"
	" %d\n", index, BitArrayGet(bit_arr, index));
	index = 5;
	printf("The value of index %lu is:"
	" %d\n", index, BitArrayGet(bit_arr, index));
	
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	bit_arr = BitArrayFlip(bit_arr, index);
	printf("The value of index %lu ater flip is:"
	" %d\n", index, BitArrayGet(bit_arr, index));
	printf("The num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	bit_arr = BitArrayMirror(bit_arr);
	printf("After mirror the num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(bit_arr, dest));
	
	step = 5;
	bit_arr = BitArrayRotateRight(bit_arr, step);
	printf("After rotate %lu times right, the num %lu represented to bit"
	" in a string is:\n%s\n", step, bit_arr, BitArrayToString(bit_arr, dest));
	
	step = 20;
	bit_arr = BitArrayRotateLeft(bit_arr, step);
	printf("After rotate %lu times right, the num %lu represented to bit"
	" in a string is:\n%s\n", step, bit_arr, BitArrayToString(bit_arr, dest));
}

void InitCountLut(size_t table[])
{
	int i = 0;
	
	for (i = 0; i < 256; ++i) 
	{
		table[i] = (i & 1) + table[i / 2];
	}
}

size_t CountBitsLut(size_t n, size_t table[]) 
{
	size_t count = table[n & 0xff];
	
	count += table[(n >> 8) & 0xff];
	count += table[(n >> 16) & 0xff];
	count += table[(n >> 24) & 0xff];
	count += table[(n >> 32) & 0xff];
	count += table[(n >> 40) & 0xff];
	count += table[(n >> 48) & 0xff];
	count += table[(n >> 56) & 0xff];
	
	return count;
}

void InitMirrorTable(size_t mirror_table[]) 
{
	size_t i = 0;
	size_t j = 0;
	size_t reversed = 0;

	for (i = 0; i < 256; ++i) 
	{
		reversed = 0;
		
		for (j = 0; j < 8; ++j) 
		{
			if (i & (1 << j)) {
				reversed |= (size_t)1 << (7 - j);
			}
		}
		mirror_table[i] = reversed;
	}
}

bit_array_t MirrorBitsLut(bit_array_t n, size_t mirror_table[]) 
{
    return (mirror_table[n & 0xff] << 56) | (mirror_table[(n >> 8) & 0xff] << 48) |
           (mirror_table[(n >> 16) & 0xff] << 40) | (mirror_table[(n >> 24) & 0xff] << 32) |
           (mirror_table[(n >> 32) & 0xff] << 24) | (mirror_table[(n >> 40) & 0xff] << 16) |
           (mirror_table[(n >> 48) & 0xff] << 8) | mirror_table[(n >> 56) & 0xff];
}


void LutCountOn()
{
	bit_array_t bit_arr = 7;
	size_t count_on_table[256] = {0};
	size_t mirror_table[256] = {0};
	char dest[64] = {OFF};
	
	InitCountLut(count_on_table);
	
	printf("The num of set bits (loop_func) is: %lu\n", BitArrayCountOn(bit_arr));
	printf("The num of set bits (LUT) is: %lu\nSUCCESS\n", CountBitsLut(bit_arr, count_on_table));
	
	InitMirrorTable(mirror_table);
	
	printf("After mirror (bit_mirror_func) the num %lu represented to bit in a string is:"
	"\n%s\n", bit_arr, BitArrayToString(BitArrayMirror(bit_arr), dest));
	printf("After mirror (LUT) the num %lu represented to bit in a string is:"
	"\n%s\nSUCCESS\n", bit_arr, BitArrayToString(MirrorBitsLut(bit_arr, mirror_table), dest));
}
