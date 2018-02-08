#include <stdio.h>
#include <string.h>
#include <doublebuffer.h>
#include <file.h>

void readfile1(int chunk, FILE *file_ptr) {



    int block=0;
    int pos=0;
    int count=0;
    int index=0;
    char c;


    count = doublebuffer_create(chunk, file_ptr);
    while (count >0 ){
        pos++;
        for (index = block*chunk; index < block*chunk+count; index++) {
            printf("%c",doublebuffer_getchar(index));
        }
        block=pos%2;
        count = doublebuffer_load(block);
    }
    doublebuffer_destroy();
}


void readfile2(int chunk, FILE *file_ptr) {



    int block=0;
    int pos=0;
    int count=0;
    char c;

    doublebuffer_create(chunk, file_ptr);
    while(!doublebuffer_hasfinished()) {
        c = doublebuffer_nextchar();
        printf("%c", c);
    }
    doublebuffer_destroy();

}

int main ( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    } else  {
		FILE *file_ptr;
		int chunk = 0;

		for (chunk=32; chunk<=64; chunk=chunk*2) { 
			file_ptr = openfile(argv[1]);
		    if (file_ptr) {
		        readfile1(chunk, file_ptr);
		        printf("Chunk: %d\n", chunk);
		        closefile(file_ptr);
		    }
			file_ptr = openfile(argv[1]);
		    if (file_ptr) {
		        readfile2(chunk, file_ptr);
		        printf("Chunk: %d\n", chunk);
		        closefile(file_ptr);
		    }
		}
	}
}

