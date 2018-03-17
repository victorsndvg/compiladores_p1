#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Nodo de una lista enlazada
struct node { 
    struct node *next; //puntero al siguiente nodo
    char *lex;         //lexema
    int  code;         //código del lexema
};

#define HASHSIZE 201   // tamaño de la table
static struct node *hashtab[HASHSIZE]; //tabla hash de nodos

//Funcion para imprimir un nodo por pantalla
void printnode(struct node *thenode) {
    if (thenode == NULL) {
        printf("  -> NULL node\n");
    } else {
        printf(" (%04d) %s \n", thenode->code, thenode->lex);
    }
}

//Funcion para imprimir una lista de nodos
void printnodelist(int level, struct node *thenode) {
    if (thenode) {
        if (thenode->next) {
            printnodelist(level+1, thenode->next);
        }
        printf(" (%04d) (%02d) %s \n", thenode->code, level, thenode->lex);
    }
}

//Funcion para liberar una lista de nodos
void freenode(struct node *thenode) {
    if (thenode) {
        if (thenode->next) {
            freenode(thenode->next);
            thenode->next == NULL;
        }
        if (thenode->lex) {
            free(thenode->lex);
            thenode->lex == NULL;
        }
        free(thenode);
        thenode = NULL;
    }
}

//Copiado de cadenas
char *customstrdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
       strcpy(p, s);
    return p;
}

//Funcion hash
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

//Busca un nodo en la tabla apartir de un lexema
struct node *lookup(char *s) {
    struct node *current;
    for (current = hashtab[hash(s)]; current != NULL; current = current->next)
        if (strcmp(s, current->lex) == 0)
          return current; 
    return NULL; 
}

//Libear la tabla
void freedictionary() {
    int index;
    for (index = 0; index < HASHSIZE; index += 1) 
        freenode(hashtab[index]);
}

//Libear la tabla
void printdictionary() {
    printf("###############################\n");
    printf("Tabla de símbolos\n");
    printf("###############################\n");
    int index;
    for (index = 0; index < HASHSIZE; index += 1) 
        printnodelist(0, hashtab[index]);
}

//Inserta lexemas en el diccionario
struct node *push(char *lex, int defaultcode) {
    struct node *current;
    struct node *previous;
    unsigned hashval;
    if (lex == NULL)
        return NULL;
	//Si no encuentra el lexema a insertar
    if ((current = lookup(lex)) == NULL) {
        current = (struct node *) malloc(sizeof(*current));
        if (current == NULL)
            return NULL;
        current->lex = customstrdup(lex);
        current->code = defaultcode;
        hashval = hash(lex);
        current->next = hashtab[hashval];
        hashtab[hashval] = current;
        return current;
	//Si el lexema ya estaba presente en el dicionario
    } else {
        previous = (struct node *) malloc(sizeof(*previous));
        if (previous == NULL)
            return NULL;
        previous->lex = customstrdup(lex);
        previous->code = current->code;
        hashval = hash(lex);
        previous->next = current; 
        hashtab[hashval] = previous;
        return previous;
    }
}

//Elimina un lexema del dicionario
struct node *pop(char *s) {
    struct node *current;
    for (current = hashtab[hash(s)]; current != NULL; current = current->next)
        if (strcmp(s, current->lex) == 0) {
            hashtab[hash(s)] = current->next;
            current->next = NULL;
            return current; /* found */
        }
    return NULL; 
}
