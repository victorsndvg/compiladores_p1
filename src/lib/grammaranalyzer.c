#include <stdio.h>
#include <stdlib.h>
#include <lexanalizer.h>
#include <dictionary.h>
#include <doublebuffer.h>

//Inicializa la tabla de simbolos con las palabras reservadas
void initialize(int chunk, FILE *file_ptr){
    doublebuffer_create(chunk, file_ptr);
    initialize_dictionary();
}

//Desaloja la memoria del buffer y diccionario
void destroy() {
    doublebuffer_destroy();
    printdictionary(0);
    freedictionary();
}

//Obtiene los lexemas desde el diccionario y los imprime por pantalla
int grammar_analyze () {
	struct node *lex;
	int newline = 0;

#ifdef DEBUG
	printf("%03d ", counter++);
#endif
	lex = lex_nextlex();
    while (lex) {
		printnode(lex);
#ifdef DEBUG 
		printf("%03d ", counter++);
#endif
        lex = lex_nextlex();
    }
}
