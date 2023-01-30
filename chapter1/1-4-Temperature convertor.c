/*
* Write a program to print the corresponding Celsius to Fahrenheit table.
*/

#include <stdio.h>

int main() {
	float fahr, celsius;
	int lower, upper, step;

	lower = -20;
	upper = 140;
	step = 10;

	celsius = lower;
	printf("Celsius\tFahrenheit\n");
	printf("------------------\n");
	while (celsius <= upper) {
		fahr = (9.0 * celsius) / 5.0 + 32.0;
		printf("%3.0f %6.0f\n", celsius, fahr);
		celsius = celsius + step;
	}
}