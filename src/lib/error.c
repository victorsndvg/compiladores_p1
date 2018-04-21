#include <stdio.h>

void openfile_error(char * filename) {
    printf("ERROR: openning %s.\n", filename);
}

void closefile_error() {
    printf("ERROR: closing file.\n");
}

void dictionary_error() {
    printf("ERROR: null dictionary node.\n");
}

void lexical_error() {
    printf("ERROR: unrecognized lex.\n");
}
