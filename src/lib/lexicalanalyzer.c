#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file.h>
#include <doublebuffer.h>
#include <statetransition.h>
#include <dictionary.h>
#include <definitions.h>
#include <error.h>


//Devuelve el proximo caracter desde el doble buffer
char lex_nextchar() {
    char c = EOF;
    if(!doublebuffer_hasfinished()) {
        c = doublebuffer_nextchar();
    }
    return c;
}

//Libera un lexema
void lex_free(char *lex) {
    if(lex) {
        free(lex);
        lex = NULL;
    }
}

//Reconocimiento del tipo de lexema (digito, hexadecimal o cadena)
int return_type(int state, int default_ID) {
    if (state == DIGITLEX) {
        return _NUM;
    } else if (state == HEXDIGITLEX) {
        return _HEX;
    } else if (state == STRINGLEX) {
        return _STRING;
    }
    return default_ID;
}

//Analiza caracteres hasta que acepta un lexema y lo devuelve.
struct node *lex_nextlex(){
	char currentchar;
	char previouschar;
    int type = 0;
	int previousstate = ACCEPT;
	int currentstate = ACCEPT;
    char *lex = NULL;
	struct node *thenode=NULL;

    // Mientras no alcancemos el final del fichero
	while (currentchar != EOF) {
		currentchar = lex_nextchar();
        // Calculo del estado actual a partir del caracter actual
        currentstate = statetransition(currentchar, currentstate);
        // Estado de error
        if (currentstate == ERROR){
            lexical_error();
            currentstate = ACCEPT;
        // Aceptacion de un lexema con el siguiente caracter 
        } else if (currentstate == NEWLINE){
            thenode = newnode("\\n", _NEWLINE);
            currentchar = previouschar;
            currentstate = previousstate;
            return thenode;
		} else if (currentstate == STEPBACK){
            doublebuffer_stepback();
            lex = doublebuffer_getsubstring();
            type = return_type(previousstate, _ID);
            if (type == _ID) {
			    thenode = push(lex, type);
            } else {
                thenode = newnode(lex, type);
            }
            doublebuffer_accept();
#ifdef DEBUG 
			printf(" |%02d->%02d|", previousstate, currentstate);
#endif
			currentstate = ACCEPT;
            lex_free(lex);
            return thenode;
        // Aceptacion de lexemas de commentarios
		} else if ((previousstate == COMMENTLEX || previousstate == MULTICOMMENTLEX || previousstate == MULTICOMMENTENDLEX)  && (currentstate == ACCEPT)){
            doublebuffer_accept();
        // Aceptacion estandar con la transicion de aceptacion
		} else if ((previousstate != ACCEPT) && (currentstate == ACCEPT || currentchar == EOF)){
            lex = doublebuffer_getsubstring();
	    	type = return_type(previousstate, _ID);
            if (type == _ID) {
			    thenode = push(lex, type);
            } else {
                thenode = newnode(lex, type);
            }
            doublebuffer_accept();
#ifdef DEBUG 
			printf(" |%02d->%02d|", previousstate, currentstate);
#endif
            lex_free(lex);
            return thenode;
        } else if (currentstate == ACCEPT){
            doublebuffer_advance();
		}
		previouschar = currentchar;
		previousstate = currentstate;
        lex_free(lex);

    }
    return NULL;
}
