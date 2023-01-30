/*
* Write a program to print a histogram of the lengths of words in its input. 
* It is easy to draw the histogram with the bars horizontal. a vertical orientation
* is more challenging
*/
#include <stdio.h>
#define MAX_LENGTH 100

int main() {
	int c;
	int lword[MAX_LENGTH];
	int length = 0;
	int max_word_length = 0;
	int max_word_count = 0;

	// initialize array lword
	for (int i = 0; i < MAX_LENGTH; i++) {
		lword[i] = 0;
	}

	// count word length and stor in lword
	while ((c = getchar()) != EOF) {
		if (c == '\t' || c== ' ' || c=='\n') {
			if (length > MAX_LENGTH) {
				printf("there is word with length %d, which outperform limit %d, the program will abort!!!", length, MAX_LENGTH);
				return 1;
			}
			else if (length > 0) {
				lword[length - 1]++;

				// update max_word_length
				if (length > max_word_length) {
					max_word_length = length;
				}
				// update max_word_count
				if (lword[length - 1] > max_word_count) {
					max_word_count = lword[length - 1];
				}
				length = 0;

			}
		}
		else{
			length++;
		}
	}

	// horizontal histogram
	printf("\n\nhorizontal histogramn\n");

	for(int index_row=0; index_row < max_word_length; index_row++){

		printf("%3d|", (index_row +1));
		for (int index_column = 1;index_column <= lword[index_row]; index_column++) {
			putchar('*');
		}
		putchar('\n');
	} ;

	// vertical histogram
	printf("\n\nvertical histogramn\n");

	for (int index_row = max_word_count; index_row >= 0; index_row--) {
		
		if (index_row == 0) {
			for (int index_column = 0; index_column < max_word_length; index_column++) {
				printf("--");
			}
			putchar('\n');
			for (int index_column = 0; index_column < max_word_length; index_column++) {
				printf("%2d", (index_column + 1));
			}
		}
		else {
			for (int index_column = 0; index_column < max_word_length; index_column++) {
				if (lword[index_column] >= index_row) {
					printf("%2c", '*');
				}
				else {
					printf("  ");
				}
			}
			putchar('\n');
		}
	}
return 0;
}