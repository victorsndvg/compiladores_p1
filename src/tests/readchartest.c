#include <stdio.h>
#include <string.h>
#include <file.h>

int main ( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    } else  {
		FILE *file_ptr;
		char c;

		file_ptr = openfile(argv[1]);

		if (file_ptr) {
			while (c != EOF) {
				c = nextchar(file_ptr);
				if ( c == ' ' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',') {
					printf("\n");
				} else {
					printf("%c", c);
				}
				if ( c == ' ' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',') {
					printf("\n");
				}
				}
			closefile(file_ptr);
		}
	}
}

