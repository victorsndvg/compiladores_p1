#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <statetransition.h>

int scapechar = 0;

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

int point_status(char c, int status) {
	if (isdigit(c)) {
		status = DIGITLEX;
	} else {
		status = STEPBACK;
	}
    return status;
}

int operatormultichar_status(char c, int status) {
	if (isdigit(c) || isalpha(c) || c == ' ' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',' || c == ';') {
		status = STEPBACK;
	} else {
		status = ACCEPT;
	}
    return status;
}

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

int string_status(char c, int status) {
	if ( c == '"' ) {
		status = ACCEPT;
	}
    return status;
}

int comment_status(char c, int status) {
	if ( c == '\0' || c == '\n') {
		status = ACCEPT;
	}
    return status;
}

int multicommentstart_status(char c, int status) {
	if ( c == '*') {
		status = MULTICOMMENTENDLEX;
	} else {
		status = MULTICOMMENTLEX;
	}
    return status;
}

int multicommentend_status(char c, int status) {
	if ( c == '/') {
		status = ACCEPT;
	} else {
		status = MULTICOMMENTLEX;
	}
    return status;
}

int alpha_status(char c, int status) {
	if (isdigit(c) || isalpha(c) || c == '_') {
	} else {
		status = STEPBACK;
	}
    return status;
}

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
        status = initial_status(c, status);
	} else if (status == SIGNLEX) {
        status = sign_status(c, status);
	} else if (status == POINTCHAR) {
        status = point_status(c, status);
	} else if (status == OPERATORSINGLECHAR) {
        status = STEPBACK;
	} else if (status == OPERATORMULTICHAR) {
        status = operatormultichar_status(c, status);
	} else if (status == DIGITLEX || status == HEXDIGITLEX) {
        status = digit_status(c, status);
	} else if (status == STRINGLEX) {
        status = string_status(c, status);
	} else if (status == SLASHCHAR) {
        status = slashchar_status(c, status);
	} else if (status == COMMENTLEX) {
        status = comment_status(c, status);
	} else if (status == MULTICOMMENTLEX) {
        status = multicommentstart_status(c, status);
	} else if (status == MULTICOMMENTENDLEX) {
        status = multicommentend_status(c, status);
	} else if (status == ALPHALEX) {
        status = alpha_status(c, status);
	}
    return status;
}

