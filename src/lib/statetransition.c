#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <statetransition.h>

int scapechar = 0;

/*
Estado inicial. 
Filtrado do tipo a partir do primeiro caracter do lexema.
Estado posterior a aceptación.
*/
int initial_status(char c, int status) {
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
    return status;
}

//Automata de recoñecemento dun lexema que comeza con operadores (+, -)
int sign_status(char c, int status) {
	if (c == '=') {
		status = ACCEPT;
	} else if (isdigit(c)) {
		status = DIGITLEX;
	} else {
		status = STEPBACK;
	}
    return status;
}

// Recoñecemento dun dixito en punto flotante
int point_status(char c, int status) {
	if (isdigit(c)) {
		status = DIGITLEX;
	} else {
		status = STEPBACK;
	}
    return status;
}

// Recoñecemento de operadores compostos por varios caracteres
int operatormultichar_status(char c, int status) {
	if (isdigit(c) || isalpha(c) || c == ' ' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',' || c == ';') {
		status = STEPBACK;
	} else {
		status = ACCEPT;
	}
    return status;
}

// Recoñecemento de dixitos (enteiros, flotantes, exponenciais, imaxinarios e hexadecimais)
int digit_status(char c, int status) {
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
    return status;
}

// Recoñecemento de comentarios e comentarios multiliña
int slashchar_status(char c, int status) {
	if ( c == '*' ) {
		status = MULTICOMMENTLEX;
	} else if ( c == '/' ) {
		status = COMMENTLEX;
	} else {
		status = STEPBACK;
	}
    return status;
}

// Recoñecemento de strings entre comiñas dobles
int string_status(char c, int status) {
	if ( c == '"' ) {
		status = ACCEPT;
	}
    return status;
}

// Aceptación de comentarios de liña
int comment_status(char c, int status) {
	if ( c == '\0' || c == '\n') {
		status = ACCEPT;
	}
    return status;
}

// Estado inicial dos comentarios multi liña
int multicommentstart_status(char c, int status) {
	if ( c == '*') {
		status = MULTICOMMENTENDLEX;
	} else {
		status = MULTICOMMENTLEX;
	}
    return status;
}

// Aceptación dun lexema comentario multi liña
int multicommentend_status(char c, int status) {
	if ( c == '/') {
		status = ACCEPT;
	} else {
		status = MULTICOMMENTLEX;
	}
    return status;
}

// Rexoñecemento de lexemas alphanuméricos
int alpha_status(char c, int status) {
	if (isdigit(c) || isalpha(c) || c == '_') {
	} else {
		status = STEPBACK;
	}
    return status;
}

//Analiza el cambio de estado desde un estado de inicio o aceptación dado un nuevo caracter
int statetransition(char c, int status) {

    if ( c == '\\') {
			scapechar = 1;
            return status;
	} else if (scapechar) {
			scapechar = 0;
            return status;
    }

    // Partimos dun estado inicial ou de aceptación
	if (status == ACCEPT) {
        status = initial_status(c, status);
    // Se o primeiro caracter e o operador + ou -
	} else if (status == SIGNLEX) {
        status = sign_status(c, status);
    // Cambio de estado o atopar o caracter .
	} else if (status == POINTCHAR) {
        status = point_status(c, status);
    // Recoñecemento de operadores dun unico caracter
	} else if (status == OPERATORSINGLECHAR) {
        status = STEPBACK;
    // Recoñecemento de operadores multi caracter
	} else if (status == OPERATORMULTICHAR) {
        status = operatormultichar_status(c, status);
    // Recoñecemento de díxitos
	} else if (status == DIGITLEX || status == HEXDIGITLEX) {
        status = digit_status(c, status);
    // Recoñecemento de strings entre comiñas dobles
	} else if (status == STRINGLEX) {
        status = string_status(c, status);
    // Recoñecemento de primeiro caracter de comentario
	} else if (status == SLASHCHAR) {
        status = slashchar_status(c, status);
    // Recoñecemento de comentarios de unha liña
	} else if (status == COMMENTLEX) {
        status = comment_status(c, status);
    // Recoñecemento de comentarios multi liña
	} else if (status == MULTICOMMENTLEX) {
        status = multicommentstart_status(c, status);
    // Aceptación de comentarios multi liña
	} else if (status == MULTICOMMENTENDLEX) {
        status = multicommentend_status(c, status);
    // Recoñecemento lexemas alfanumericos
	} else if (status == ALPHALEX) {
        status = alpha_status(c, status);
	}
    return status;
}

