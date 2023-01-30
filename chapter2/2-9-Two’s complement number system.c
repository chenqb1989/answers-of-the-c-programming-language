/*
* In a two’s complement number system, x &= (x-1) deletes the rightmost 1-bit in x. 
* Explain why. Use this observation to write a faster version of bitcount.
*/

#include <stdio.h>

int bitcount(unsigned x){
	int b;

	for (b = 0; x != 0; x&=(x-1)) {
		b++;
	}
	return b;
}

main()
{
	//a = 15(10100011)
	unsigned char a = 5;
	int c = bitcount(a);
	printf("%d", c);

}
