struct node;
void printnode(struct node *thenode);
struct node *lookup(char *s);
struct node *push(char *lex, int defaultcode);
struct node *pop(char *s);
