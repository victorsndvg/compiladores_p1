struct node;
struct node *lookup(char *s);
struct node *push(char *lex, int defaultcode);
struct node *pop(char *s);
struct node *newnode(char *lex, int code);
void printnode(struct node *thenode);
void freenode(struct node *thenode);
void freedictionary();
void printdictionary();
void initialize_dictionary();
