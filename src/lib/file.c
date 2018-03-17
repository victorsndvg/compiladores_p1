#include <stdio.h>
#include <error.h>

//Abre un fichero dada su ruta
FILE * openfile(char * filename) {

	FILE *file_ptr;

	if ( (file_ptr = fopen(filename, "r") ) == NULL) {
		openfile_error(filename);
	}
	return file_ptr;
}

//Cierra un fichero dado su puntero
void closefile(FILE * file_ptr) {

	if (fclose(file_ptr)!=0) {
		closefile_error();
	}
}

//Carga un determinado numero de caracteres desde fichero
int nextline(char * buffer, int chunk, FILE * file_ptr) {
	return fread(buffer, 1, chunk, file_ptr);
}

//Carga un caracter desde fichero
char nextchar(FILE * file_ptr) {
	return fgetc(file_ptr);
}


