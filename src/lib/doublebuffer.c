#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <file.h>

int start = 0;          //Indice de inicio de lexema
int end = 0;            //Indice de final de lexema
int chunk = 64;         //Tamaño de bloque del buffer
int block = 0;          //Identificador de bloque
int blocklength = 0;    //Longitud del la cadena a cargar en el bloque
FILE *file_ptr = NULL;  //Puntero a fichero
char *tmpbuffer;        //Bloque de buffer temporal
char * doublebuffer;    //Doble buffer

//Liberar memoria del doble buffer
void doublebuffer_destroy() {
    if(doublebuffer)
        free(doublebuffer);
    doublebuffer = NULL;
    if(tmpbuffer)
        free(tmpbuffer);
    tmpbuffer = NULL;
}

//Carga de bloque en el buffer desde fichero
int doublebuffer_load(int block) {
    int count = nextline(tmpbuffer, chunk, file_ptr);
    if(count)
        memcpy(&doublebuffer[block*(chunk)], tmpbuffer, count);
    return count;
}

//Inicialización y alojamiento de memoria del doble buffer
int doublebuffer_create(int thechunk, FILE *thefile_ptr) {
    end = 0;
    chunk = thechunk;
    file_ptr = thefile_ptr;
    doublebuffer_destroy();
    doublebuffer = (char*) malloc(2*(chunk)*(int)sizeof(char));
    tmpbuffer = (char*) malloc(chunk*(int)sizeof(char));
    blocklength = doublebuffer_load(0);
    return blocklength;
}

//Avisa del final de fichero en el buffer
int doublebuffer_hasfinished() {
    if(blocklength < chunk){
        return end >= (block*chunk)+blocklength;
    }
    return 0;
}

//Devuelve el siguiente caracter desde el buffer
char doublebuffer_nextchar() {
    char c = doublebuffer[end];
    end++;
    if(end == chunk) {
        block = 1;
        blocklength = doublebuffer_load(block);
    } else if(end == 2*chunk) {
        end = 0;
        block = 0;
        blocklength = doublebuffer_load(block);
    }
    return c;
}

//Devuelve un caracter determinado del buffer dado su indice
char doublebuffer_getchar(int index) {
    return doublebuffer[index];
}

//Avanza el caracter de inicio del lexema para la lectura de un nuevo lexema
void doublebuffer_accept() {
    start = end;
}

//Incrementa posición de inicio del lexema
void doublebuffer_advance() {
    start++;
}

//Decrementa la posición del final del lexema.
void doublebuffer_stepback() {
    end--;
}

//Devuelvve el lexema entre start y end
char *doublebuffer_getsubstring() {
    int i;
    int index=0;
    char *substring;
#ifdef DEBUG 
	printf("<%03d,%03d> ", start, end);
#endif
    if(end < start){
        substring = (char*) malloc(((2*chunk)-start+end)*(int)sizeof(char));
        for(i=start; i<2*chunk; i++) {
            substring[index] = doublebuffer[i];
            index++;
        }
        for(i=0; i<end; i++) {
            substring[index] = doublebuffer[i];
            index++;
        }
    } else {
        substring = (char*) malloc((end-start)*(int)sizeof(char));
        memcpy( substring, &doublebuffer[start], end-start );
    }
    return substring;
}



