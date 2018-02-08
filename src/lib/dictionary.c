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

//Inserta lexemas en el diccionario
struct node *push(char *lex, int defaultcode) {
    struct node *current;
    struct node *previous;
    unsigned hashval;
	//Si no encuentra el lexema a insertar
    if ((current = lookup(lex)) == NULL) {
        current = (struct node *) malloc(sizeof(*current));
        if (current == NULL || (current->lex = customstrdup(lex)) == NULL)
            return NULL;
        current->code = defaultcode;
        hashval = hash(lex);
        current->next = hashtab[hashval];
        hashtab[hashval] = current;
        return current;
	//Si el lexema ya estaba presente en el dicionario
    } else {
        previous = (struct node *) malloc(sizeof(*previous));
        if (previous == NULL || (previous->lex = customstrdup(lex)) == NULL)
            return NULL;
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
