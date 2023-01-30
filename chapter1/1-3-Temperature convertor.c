/* 
* Modify the temperature conversion program to print a heading above the table.
*/
 
#include <stdio.h>

int main() {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;
	printf("Fahrenheit\tCelsius\n");
	printf("----------------------\n");
	while (fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf("%6.0f %12.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}