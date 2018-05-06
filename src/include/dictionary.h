struct node;
struct node *lookup(char *s);
struct node *push(char *lex, int defaultcode);
struct node *pop(char *s);
void printnode(struct node *thenode);
void freenode(struct node *thenode);
void freedictionary();
void printdictionary();
void initialize_dictionary();
