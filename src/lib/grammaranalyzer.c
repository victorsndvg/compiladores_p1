#include <stdio.h>
#include <stdlib.h>
#include <definitions.h>
#include <lexanalizer.h>
#include <dictionary.h>

//Obtiene los lexemas desde el diccionario y los imprime por pantalla
int grammar_analyze (int chunk, FILE *file_ptr) {
	struct node *lex;
	int counter = 0;

    lex_create(chunk, file_ptr);
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
    lex_destroy();
}
