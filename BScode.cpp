#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_SIZE sizeof(int) * 8

typedef unsigned short ushort;

int *setBit(unsigned short pos, unsigned short bitValue, int *n);

int main(void) {

	int n = 0;
	printf("n = %d\n");
	printf("n = %d\n", setBit(0, 1, &n));
	printf("n = %d\n", setBit(0, 0, &n));
	printf("n = %d\n", setBit(1, 0, &n));

	for (ushort pos = 0; pos < INT_SIZE; ++pos)
		setBit(pos, 1, &n);
	printf("n = %d\n", n);

	int m = -1;
	printf("m = %d\n", setBit(31, 0, &m));

	return EXIT_SUCCESS;
}

int *setBit(unsigned short pos, unsigned short bitValue, int *n) {
	assert(pos < INT_SIZE);
	assert(bitValue == 0 || bitValue == 1);
	// Variante 1
	const int MASK_1 = 1 << pos;
	const int MASK_2 = bitValue << pos;
	*n = (*n & MASK_1) | MASK_2;
/*	{// Variante 2
		const int MASK = 1 << pos;
		*n ^= (-bitValue ^ *n) & MASK;
	}
	{// Variante 3
		const int MASK = 1 << pos;
		*n = bitValue ? *n | MASK : *n & -MASK; // ... mais usage de ?:
	}*/
	return n;
}