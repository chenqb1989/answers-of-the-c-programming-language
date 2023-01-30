/*
* Rewrite the routines day_of_year and month_day with pointers instead of indexing.
*/

#include <stdio.h>

static int daytab[][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
void month_day(int, int, int*, int*);

int main()
{
	int m, d;
	month_day(1988, 60, &m, &d);
	int day = day_of_year(1988, 2, 29);

	printf("month is: %d, day is: %d of 60th day in 1988\n", m, d);
	printf("the day is %dth day in February 29, 1988\n", day);

	return 0;
}

/* set day of year from month & day */
int day_of_year(int year, int month, int day) {
	int i, leap;
	if (year < 1900 || year > 9999) {                        /* check year */
		printf("error: invalid year %d\n", year);
		return -1;
	}                                
		
	if (month < 1 || month > 12) {                           /* check month */
		printf("error: invalid month %d\n", month);
		return -1;
	}
		

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if (day <= 0 || day > *(*(daytab + leap) + month)) {               /* check day, using pointers */
		printf("error: invalid day %d\n", day);
		return -1;
	}
		

	for (i = 1; i < month; i++)
		day += *(*(daytab + leap) + i);

	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	if (year < 1900 || year > 9999) {                           /* check year */
		printf("error: invalid year %d\n", year);
		return;
	}                               

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	int sumday;
	for (i = 1, sumday = 0; i < 14; i++)
		sumday += *(*(daytab + leap) + i);
	if (yearday < 0 || yearday > sumday)
		printf("error: invalid yearday %d\n", yearday);

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= *(*(daytab + leap) + i);
	*pmonth = i;
	*pday = yearday;
}