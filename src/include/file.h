FILE * openfile(char * filename);
void closefile(FILE * file_ptr);
int nextline(char * buffer, int chunk, FILE * file_ptr);
char nextchar(FILE * file_ptr);
