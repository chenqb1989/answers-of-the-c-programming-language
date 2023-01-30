/* 
* Excercise 1-2. Experiment to find out what happens when printf's argument
* string contains \c, where c is some character not listed above
*/

#include <stdio.h>

main() {
	printf("hello, ");
	printf("world");
	printf("\n");
	printf("\a\c\d\e\f\g\h\i\j\k\l\m\o\p\q\s\u\v\w"); /* without \r */
	printf("\a\c\d\e\f\g\h\i\j\k\l\m\o\p\q\r\s\u\v\w"); /* with \r */
}