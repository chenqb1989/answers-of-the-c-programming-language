/*
* Our binary search makes two tests inside the loop, when one would suffice 
* (at the price of more tests outside.) Write a version with only one test 
* inside the loop and measure the difference in runtime.
*/

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#define N 10000

int binsearch(int x, int v[], int n);  /* two comparition in while*/
int binsearch2(int x, int v[], int n);  /* one comparition in while*/

int main()
{
	int v[N];
	int input = 5000; /* chech time consuming when input is -10, 1000, 5000, 9000, 11000 and so on*/
	int times = 10000000;

	//printf("array values: ");
	for (int i = 0; i < N; i++) {
		v[i] = i;
		//printf("%d ", v[i]);
	}

	int i, j;
	i = j = 0;
	int out1, out2;
	clock_t t1 = clock();
	while (i++ <times)
		out1 = binsearch(input, v, N);
	clock_t t2 = clock();
	while (j++ < times)
		out2 = binsearch2(input, v, N);
	clock_t t3 = clock();
	double time1 = (double)(t2 - t1) / CLOCKS_PER_SEC;
	double time2 = (double)(t3 - t2) / CLOCKS_PER_SEC;

	printf("\nbinsearch: idx of %d in the array is %d, search %d times consuming time: %.4f", input, out1, times, time1);
	printf("\nbinsearch2: idx of %d in the array is %d, search %d times consuming time: %.4f", input, out2, times, time2);

	return 0;
}

int binsearch(int x, int v[], int n) {
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	
	return -1;
}

int binsearch2(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	if (v[low] == x)
		return low;
	else
		return -1;
}