#include <stdio.h>
#include <stdlib.h>
#include <definitions.h>
#include <lexanalizer.h>
#include <dictionary.h>
#include <doublebuffer.h>

//Inicializa la tabla de simbolos con las palabras reservadas
void lex_initialize(){
    push("package", _PACKAGE);
    push("import", _IMPORT);
    push("func", _FUNC);
    push("var", _VAR);
    push("chan", _CHAN);
    push("for", _FOR);
    push("range", _RANGE);
    push("range", _RANGE);
    push("real", _REAL);
    push("make", _MAKE);
    push("go", _GO);
    push("len", _LEN);
    push("float32", _FLOAT32);
    push("sum", _SUM);
    push("==", _EQCOMP);
    push(":=", _ASSIGN);
    push("+=", _INCREASE);
    push("<-", _SEND);
    push("(", _OP);
    push(")", _CP);
    push("[", _OB);
    push("]", _CP);
    push("{", _OCB);
    push("}", _CCB);
    push(",", _COMMA);
    push(":", _C);
    push(";", _SC);
    push("/", _DIV);
    push("=", _EQ);
    push("+", _SUMM);
    push("-", _MINUS);
    push(".", _POINT);
}

//Inicializa el analizador lexico
void lex_create(int chunk, FILE *file_ptr) {
    doublebuffer_create(chunk, file_ptr);
	lex_initialize();
}

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
