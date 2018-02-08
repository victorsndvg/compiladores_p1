int doublebuffer_create(int thechunk, FILE *thefile_ptr);
void doublebuffer_destroy();
int doublebuffer_load(int index);
int doublebuffer_hasfinished();
char doublebuffer_nextchar();
char doublebuffer_getchar();
void doublebuffer_accept();
void doublebuffer_stepback();
void doublebuffer_advance();
char *doublebuffer_getsubstring();
