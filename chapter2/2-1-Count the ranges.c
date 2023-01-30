/*
* Write a program to determine the ranges of char, short, int, 
* and long variables, both signed and unsigned, by printing appropriate
* values from standard headers and by direct computation. Harder if you compute them: 
* determine the ranges of the various floating-point types.
*/

/*
Program of direct computation refer below code
https://stackoverflow.com/questions/8305967/how-to-determine-the-ranges-of-floating-point-types-using-direct-computation
*/

#include <stdio.h>
#include <limits.h>

#define TESTBIT 2

void type_range_standard();
void type_range_computation();

main()
{
	type_range_standard();
	type_range_computation();
}

void type_range_standard() {
	printf("signed char range: %d -- %d\n", CHAR_MIN, CHAR_MAX);
	printf("unsigned char range: %u -- %u\n", 0, UCHAR_MAX);
	printf("signed short range: %d -- %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short range: %u -- %u\n", 0, USHRT_MAX);
	printf("signed int range: %d -- %d\n", INT_MIN, INT_MAX);
	printf("unsigned int range: %u -- %u\n", 0, UINT_MAX);
	printf("signed long range: %d -- %d\n", LONG_MIN, LONG_MAX);
	printf("unsigned long range: %u -- %u\n", 0, ULONG_MAX);
}

void type_range_computation() {
	char ch, chtest;
	unsigned char uch;
	short sh, shtest;
	unsigned short ush;
	int i, itest;
	unsigned int ui;
	long l, ltest;
	unsigned long ul;
	long long ll, lltest;
	unsigned long long ull;
	float fl, fltest, last;
	double dbl, dbltest, dblast;

	ch = uch = sh = ush = i = ui = l = ul = ll = ull = 0;
	fl = 0.0;
	fltest = 0.0;
	dbl = 0.0;
	dbltest = 0.0;

	++ch;        /* Maximum and minimum ranges using direct computation */
	chtest = 0;
	while (chtest >= 0) {
		chtest = ch * TESTBIT;
		if (chtest > 0)
			ch = ch * TESTBIT;
	}
	ch = ch * 2;
	printf("Minimum range of signed char variable: %d\n", ch);

	--ch;
	printf("Maximum range of signed char variable: %d\n", ch);

	--uch;
	printf("Maximum range of unsigned char variable: %u\n", uch);

	++sh;
	shtest = 0;
	while (shtest >= 0) {
		shtest = sh * TESTBIT;
		if (shtest > 0)
			sh = sh * TESTBIT;
	}
	sh = sh * 2;
	printf("Minimum range of signed short variable: %d\n", sh);

	--sh;
	printf("Maximum range of signed short variable: %d\n", sh);

	--ush;
	printf("Maximum range of unsigned short variable: %u\n", ush);

	++i;
	itest = 0;
	while (itest >= 0) {
		itest = i * TESTBIT;
		if (itest > 0)
			i = i * TESTBIT;
	}
	i = i * 2;
	printf("Minimum range of signed int variable: %d\n", i);

	--i;
	printf("Maximum range of signed int variable: %d\n", i);

	--ui;
	printf("Maximum range of unsigned int variable: %u\n", ui);

	++l;
	ltest = 0;
	while (ltest >= 0) {
		ltest = l * TESTBIT;
		if (ltest > 0)
			l = l * TESTBIT;
	}
	l = l * 2;
	printf("Minimum range of signed long variable: %d\n", l);

	--l;
	printf("Maximum range of signed long variable: %d\n", l);

	--ul;
	printf("Maximum range of unsigned long variable: %lu\n", ul);

	++ll;
	lltest = 0;
	while (lltest >= 0) {
		lltest = ll * TESTBIT;
		if (lltest > 0)
			ll = ll * TESTBIT;
	}
	ll = ll * 2;
	printf("Minimum range of signed long long variable: %lld\n", ll);

	--ll;
	printf("Maximum range of signed long long variable: %lld\n", ll);

	--ull;
	printf("Maximum range of unsigned long long variable: %llu\n", ull);

	while (fl == 0.0) {
		last = fltest;
		fltest = fltest + 1111e28;
		fl = (fl + fltest) - fltest;
	}
	printf("Maximum range of float variable: %e\n", last);

	while (dbl == 0.0) {
		dblast = dbltest;
		dbltest = dbltest + 1111e297;
		dbl = (dbl + dbltest) - dbltest;
	}
	printf("Maximum range of double variable: %e\n", dblast);
}