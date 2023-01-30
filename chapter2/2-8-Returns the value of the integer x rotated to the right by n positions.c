/*
* Write a function rightrot(x,n) that returns the value of the 
* integer x rotated to the right by n positions.
*/

#include <stdio.h>
#include <climits>

unsigned char rightrot(unsigned char x, int n)
{
	unsigned char nbits;

	nbits = ~(~0 << n);  /* mask to extract rightmost n bits */
	int bit = CHAR_BIT;

	return ((x >> n) | ((x & nbits) << ((sizeof(x) * bit) - n)));
}

main()
{
	//a = 15(10100011)
	unsigned char a = 163;
	unsigned c = rightrot(a, 5);
	printf("%u", c);

}