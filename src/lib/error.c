#include <stdio.h>

//error al abrir el fichero
void openfile_error(char * filename) {
    printf("ERROR: openning %s.\n", filename);
}

//error al cerrar el fichero
void closefile_error() {
    printf("ERROR: closing file.\n");
}

//error con las operaciones del diccionario
void dictionary_error() {
    printf("ERROR: null dictionary node.\n");
}

//error lexico
void lexical_error() {
    printf("ERROR: unrecognized lex.\n");
}
