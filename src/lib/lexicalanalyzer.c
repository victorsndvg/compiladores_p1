#include <stdio.h>
#include <string.h>
#include <file.h>
#include <doublebuffer.h>
#include <statetransition.h>
#include <dictionary.h>
#include <definitions.h>

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

//Devuelve el proximo caracter desde el doble buffer
char lex_nextchar() {
    char c = EOF;
    if(!doublebuffer_hasfinished()) {
        c = doublebuffer_nextchar();
    }
    return c;
}

//Desaloja la memoria del buffer
void lex_destroy() {
    doublebuffer_destroy();
}

//Analiza caracteres hasta que acepta un lexema y lo devuelve.
struct node *lex_nextlex(){
	char currentchar;
	char previouschar;
	int previousstate = ACCEPT;
	int currentstate = ACCEPT;
    char *lex;
	struct node *thenode=NULL;

	while (currentchar != EOF) {
		currentchar = lex_nextchar();
        currentstate = statetransition(currentchar, currentstate);
		if (currentstate == STEPBACK){
            doublebuffer_stepback();
            lex = doublebuffer_getsubstring();
			thenode = push(lex, _ID);
            doublebuffer_accept();
#ifdef DEBUG 
			printf(" |%02d->%02d|", previousstate, currentstate);
#endif
			currentstate = ACCEPT;
            return thenode;
		}else if ((previousstate == COMMENTLEX || previousstate == MULTICOMMENTLEX || previousstate == MULTICOMMENTENDLEX)  && (currentstate == ACCEPT)){
            doublebuffer_accept();
		}else if ((previousstate != ACCEPT) && (currentstate == ACCEPT || currentchar == EOF)){
                lex = doublebuffer_getsubstring();
				thenode = push(lex, _ID);
                doublebuffer_accept();
#ifdef DEBUG 
				printf(" |%02d->%02d|", previousstate, currentstate);
#endif
                return thenode;
        } else if (currentstate == ACCEPT){
            doublebuffer_advance();
		}
		previouschar = currentchar;
		previousstate = currentstate;
    }
    return NULL;
}
