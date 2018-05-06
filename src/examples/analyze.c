#include <stdio.h>
#include <file.h>
#include <dictionary.h>
#include <grammaranalyzer.h>

int main ( int argc, char *argv[] ) {
	FILE *file_ptr;
	int chunk = 256;
    if ( argc != 2 ) {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    } else  {
		file_ptr = openfile(argv[1]);
		if (file_ptr) {
            initialize(chunk, file_ptr);
			grammar_analyze();
            destroy();
		}
	}
}
