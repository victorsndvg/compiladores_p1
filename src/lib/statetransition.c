#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <statetransition.h>

int scapechar = 0;

//Analiza el cambio de estado desde un estado previo hasta el actual dado un nuevo caracter
int statetransition(char c, int status) {

    if ( c == '\\') {
			scapechar = 1;
            return status;
	} else if (scapechar) {
			scapechar = 0;
            return status;
    }

    // If we come from an initial or an acceptance state
	if (status == ACCEPT) {
        if ( c == '-' || c == '+') {
			status = SIGNLEX;
		} else if (c == '"') {
			status = STRINGLEX;
		} else if (c == '/') {
			status = SLASHCHAR;
		} else if (c == '.') {
			status = POINTCHAR;
		} else if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',' || c == ';') {
			status = OPERATORSINGLECHAR;
		} else if (c == '<' || c == '>' || c == ':' || c == '=' ) {
			status = OPERATORMULTICHAR;
		} else if (isdigit(c) ) {
			status = DIGITLEX;
		} else if (isalpha(c) || c == '_') {
			status = ALPHALEX;
		} else {
			status = ACCEPT;
		}
	} else if (status == SIGNLEX) {
		if (c == '=') {
			status = ACCEPT;
		} else if (isdigit(c)) {
			status = DIGITLEX;
		} else {
			status = STEPBACK;
		}
	} else if (status == POINTCHAR) {
		if (isdigit(c)) {
			status = DIGITLEX;
		} else {
			status = STEPBACK;
		}
	} else if (status == OPERATORSINGLECHAR) {
        status = STEPBACK;
	} else if (status == OPERATORMULTICHAR) {
		if (isdigit(c) || isalpha(c) || c == ' ' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',' || c == ';') {
			status = STEPBACK;
		} else {
			status = ACCEPT;
		}
	} else if (status == DIGITLEX || status == HEXDIGITLEX) {
		if ( isdigit(c) || c == '-' || c == '+' || c == '.' || c == 'e' || c == 'E' || c == 'i' ) {
		} else if ( c == 'x' || c == 'X') {
			status = HEXDIGITLEX;
		} else if (isalpha(c)) {
			if (status == HEXDIGITLEX) {
			} else {
				status = ERROR;
			}
		} else {
			status = STEPBACK;
		}
	} else if (status == STRINGLEX) {
		if ( c == '"' ) {
			status = ACCEPT;
		}
	} else if (status == SLASHCHAR) {
		if ( c == '*' ) {
			status = MULTICOMMENTLEX;
		} else if ( c == '/' ) {
			status = COMMENTLEX;
		} else {
			status = STEPBACK;
		}
	} else if (status == COMMENTLEX) {
		if ( c == '\0' || c == '\n') {
			status = ACCEPT;
		}
	} else if (status == MULTICOMMENTLEX) {
		if ( c == '*') {
			status = MULTICOMMENTENDLEX;
		} else {
			status = MULTICOMMENTLEX;
		}
	} else if (status == MULTICOMMENTENDLEX) {
		if ( c == '/') {
			status = ACCEPT;
		} else {
			status = MULTICOMMENTLEX;
		}
	} else if (status == ALPHALEX) {
		if (isdigit(c) || isalpha(c) || c == '_') {
		} else {
			status = STEPBACK;
		}
	}
    return status;
}

