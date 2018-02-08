#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <file.h>
#include <statetransition.h>

int calcstatus(char c, int status) {

	if (status == ACCEPT) {
		if ( c == ' ' || c == '\0' || c == '\n' || c == '\t' ) {
            return status;
        }
		printf("%c", c);
		if ( c == '-' || c == '+') {
			status == SIGNLEX;
		} else if (isdigit(c)) {
			status = DIGITLEX;
		} else if (c == '"') {
			status = STRINGLEX;
		} else if (c == '/') {
			status = SLASHCHAR;
		} else if (isalpha(c) || c == '_') {
			status = ALPHALEX;
		} else {
			status = ACCEPT;
			printf(": Operador\n");
		}
	} else if (status == SIGNLEX) {
		printf("%c", c);
		if (isdigit(c)) {
			status = DIGITLEX;
		} else {
			status = ERROR;
			printf(": ERROR\n");
		}
	} else if (status == DIGITLEX || status == HEXDIGITLEX) {
		if ( isdigit(c) || c == '-' || c == '+' || c == '.' || c == 'e' || c == 'E' || c == 'i' ) {
		    printf("%c", c);
		} else if ( c == 'x' || c == 'X') {
		    printf("%c", c);
			status = HEXDIGITLEX;
		} else if (isalpha(c)) {
			if (status == HEXDIGITLEX) {
		        printf("%c", c);
			} else {
				status = ERROR;
				printf(": ERROR\n");
			}
		} else {
			status = ACCEPT;
		    printf(": num\n");
			calcstatus(c, status);
		}
	} else if (status == STRINGLEX) {
        printf("%c", c);
		if ( c == '"' ) {
			status = ACCEPT;
			printf(": string\n");
		}
	} else if (status == SLASHCHAR) {
		printf("%c", c);
		if ( c == '*' ) {
			status = MULTICOMMENTLEX;
		} else if ( c == '/' ) {
			status = COMMENTLEX;
		} else {
			status = ACCEPT;
			printf("\n");
            status = calcstatus(c, status);
		}
	} else if (status == COMMENTLEX) {
		if ( c == '\0' || c == '\n') {
			status = ACCEPT;
			printf(": comment\n");
		} else {
			printf("%c", c);
		}
	} else if (status == MULTICOMMENTLEX) {
		printf("%c", c);
		if ( c == '*') {
			status = MULTICOMMENTENDLEX;
		} else {
			status = MULTICOMMENTLEX;
		}
	} else if (status == MULTICOMMENTENDLEX) {
		printf("%c", c);
		if ( c == '/') {
			status = ACCEPT;
			printf(": multicomment\n");
		} else {
			status = MULTICOMMENTLEX;
		}
	} else if (status == ALPHALEX) {
		if (isdigit(c) || isalpha(c) || c == '_') {
			printf("%c", c);
		} else {
			status = ACCEPT;
			printf(": var\n");
			calcstatus(c, status);
		}
	}
    return status;
}

int main ( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    } else  {
		FILE *file_ptr;
		char currentchar;
		char previouschar;
		int previousstate = ACCEPT;
		int currentstate = ACCEPT;

		file_ptr = openfile(argv[1]);

		if (file_ptr) {
			while (currentchar != EOF) {
				currentchar = nextchar(file_ptr);
				currentstate = statetransition(currentchar, currentstate);
		//		if (previousstate == ACCEPT && previousstate == currentstate) continue;
				if (currentstate == STEPBACK){
					printf(" <%d,%d> \n", previousstate, currentstate);
					previousstate = currentstate;
					currentstate = ACCEPT;
					currentstate = statetransition(currentchar, currentstate);
				}
				if ( currentchar != ' ' && currentchar != '\0' && currentchar != '\n' && currentchar != '\t' ) {
					printf("%c", currentchar);
		//			if ((previousstate != ACCEPT) && (currentstate == ACCEPT || currentstate == STEPBACK)){
					if ((currentstate == ACCEPT)){
						printf(" <%d,%d> \n", previousstate, currentstate);
					}
				}
				previouschar = currentchar;
				previousstate = currentstate;
			}

			closefile(file_ptr);
		}
	}
}


