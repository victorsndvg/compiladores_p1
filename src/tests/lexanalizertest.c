#include <stdlib.h>
#include <definitions.h>
#include <stdio.h>
#include <string.h>
#include <doublebuffer.h>
#include <file.h>
#include <lexanalizer.h>
#include <dictionary.h>

//Inicializa la tabla de simbolos con las palabras reservadas
void initialize(int chunk, FILE *file_ptr){
    doublebuffer_create(chunk, file_ptr);

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
//    push("sum", _SUM);
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

//Desaloja la memoria del buffer y diccionario
void destroy() {
    doublebuffer_destroy();
    freedictionary();
}

int main ( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    } else  {
		FILE *file_ptr;
		int chunk = 256;
		char c;
		struct node *lex;

		//initialize();
		file_ptr = openfile(argv[1]);
		if (file_ptr) {
		    initialize(chunk, file_ptr);
		    chunk=0;
		    while (lex != NULL) {
	//        for (chunk=0;chunk < 170; chunk++) {
		        printf("%03d ", chunk++);
		        lex = lex_nextlex();
		        
		        if(lex) {
		            printnode(lex);
		        }
		    }
		    destroy();
		}
	}
}
