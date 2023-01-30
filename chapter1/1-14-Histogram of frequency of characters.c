/*
* Write a program to print a histogram of the frequencies of different characters in its input.
*/
#include <stdio.h>
#define MAX_LENGTH 93

int main() {
	int c;
	int lchar[MAX_LENGTH];
	int max_char_count = 0;

	// initialize array lchar
	for (int i = 0; i < MAX_LENGTH; i++) {
		lchar[i] = 0;
	}

	// count character and stor in lchar
	while ((c = getchar()) != EOF) {
		if (c >= '!' && c <= '~') {  /* graphical characters only (ASCII table) */
			lchar[c - '!']++;
			if (lchar[c - '!'] > max_char_count) {
				max_char_count = lchar[c - '!'];
			}
		}
	}

	 //horizontal histogram
	printf("\n\nhorizontal histogramn\n");

	for(int index_row=0; index_row < MAX_LENGTH; index_row++){
		if (lchar[index_row] > 0) {  // only print characters with counts > 0 
			printf("%c|", (index_row + '!'));
			for (int index_column = 0;index_column < lchar[index_row]; index_column++) {
				putchar('*');
			}
			putchar('\n');
		}
	} ;
}