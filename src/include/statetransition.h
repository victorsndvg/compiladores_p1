#define ACCEPT 0
#define STEPBACK 1
#define SIGNLEX 2
#define DIGITLEX 3
#define HEXDIGITLEX 4
#define ALPHALEX 5
#define STRINGLEX 6
#define SLASHCHAR 7
#define COMMENTLEX 8
#define MULTICOMMENTLEX 9
#define MULTICOMMENTENDLEX 10
#define SCAPECHAR 11
#define OPERATORSINGLECHAR 12
#define OPERATORMULTICHAR 13
#define POINTCHAR 14
#define ERROR -1

int statetransition(char c, int status);
