/*
* Define a macro swap(t,x,y) that interchanges two arguments of type t.
*/

#include <stdio.h>
#define swap(t, x, y) {t temp = x; x = y; y = temp;}

int main()
{
	int a = 10;
	int b = 20;
	swap(int, a, b);
	printf("a: %d, b: %d\n", a, b);

	return 0;

}
