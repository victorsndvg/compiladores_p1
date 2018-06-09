#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <error.h>
#include <definitions.h>

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
        dictionary_error();
    } else {
        printf(" (%04d) %s \n", thenode->code, thenode->lex);
    }
}

//Funcion para imprimir una lista de nodos
void printnodelist(int level, int hash, struct node *thenode, int recursive) {
    if (thenode) {
        if (thenode->next) {
            printnodelist(level+1, hash, thenode->next, recursive);
            if (!recursive) {
                return;
            }
        }
        printf(" [%04d] (%04d) {%02d} %s \n", hash, thenode->code, level, thenode->lex);
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
void printdictionary(int recursive) {
    printf("###############################\n");
    printf("Tabla de símbolos\n");
    printf("###############################\n");
    int index;
    for (index = 0; index < HASHSIZE; index += 1) 
        printnodelist(1, index, hashtab[index], recursive);
}

//nuevo nodo
struct node *newnode(char *lex, int code) {
    struct node *thenode;
    thenode = (struct node *) malloc(sizeof(*thenode));
    if (thenode == NULL)
        return NULL;
    thenode->lex = customstrdup(lex);
    thenode->code = code;
    return thenode;
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
        current = newnode(lex, defaultcode);
        hashval = hash(lex);
        current->next = hashtab[hashval];
        hashtab[hashval] = current;
        return current;
	//Si el lexema ya estaba presente en el dicionario
    } else {
        previous = newnode(lex, current->code);
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

void initialize_dictionary() {

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
    push("fmt", _FMT);
    push("Println", _PRINTLN);
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
