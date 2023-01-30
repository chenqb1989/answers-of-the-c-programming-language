/*
* Write a function invert(x,p,n) that returns x with the n bits that
* begin at position p inverted (i.e., 1 changed into 0 and vice versa), 
* leaving the others unchanged.
*/

#include <stdio.h>

unsigned invert(unsigned x, int p, int n){
	unsigned nbits;

	nbits = ~(~0 << n);  /* mask to extract rightmost n bits */

	return (x & ~(nbits << (p - 1))) | (nbits & ~(x & nbits << (p - 1)));
}

main()
{
	//a = 15(10100011)
	unsigned char a = 15;
	unsigned c = invert(a, 3, 2);
	printf("%u", c);

}
