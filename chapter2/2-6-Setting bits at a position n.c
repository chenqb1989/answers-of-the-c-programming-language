/*
* Write a function setbits(x,p,n,y) that returns x with the n bits that
* begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/

#include <stdio.h>

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned int setbits(unsigned x, int p, int n, unsigned y){
	unsigned nbits;

	nbits = ~(~0 << n);  /* mask to extract rightmost n bits */

	return (x & ~(nbits << (p-1))) | ((y & nbits) << (p-1));
}

main()
{
	//a = 15(10100011), b = 9(00101001)
	unsigned char a = 163, b = 41;
	unsigned c = setbits(a, 3, 2, b);
	printf("%u", c);

}
