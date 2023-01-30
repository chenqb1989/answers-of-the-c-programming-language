/*
* Write a function htoi(s), which converts a string of hexadecimal digits 
* (including an optional 0x or 0X) into its equivalent integer value. 
* The allowable digits are 0 through 9, a through f,and A through F.
*/

#include <stdio.h>
#include <ctype.h>


int htoi(char[]);

main()
{
	char s[] = "0x1120785";
	int value_int = htoi(s);
	printf("the converted int value is %d\n", value_int);

	/*int number = (int)strtol(s, NULL, 16);
	printf("strtol value is %d\n", number);*/
}

int htoi(char s[]) {
	int i = 0;
	int out = 0;
	if (s[0] == '0' && tolower(s[1] == 'x')) {
		i = 2;
	}
	for (; s[i] != '\0'; i++) {
		char c = s[i];
		if (isdigit(c)) {
			c = c - '0';
		}
		else if (c >= 'a' && c <= 'f') {
			c = c - 'a' + 10;
		}
		else if (c >= 'A' && c <= 'F') {
			c = c - 'A' + 10;
		}
		out = 16 * out + c;
	}
	return out;
}