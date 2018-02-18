#include <stdio.h>
#include <dictionary.h>

int main( int argc, const char* argv[] )
{
    printf("Añadimos:\n");
    printnode(push("uno", 1));
    printnode(push("uno", 2));
    printnode(push("uno", 3));
    printnode(push("dos", 4));
    printnode(push("uno", 5));
    printnode(push("uno", 6));
    printnode(push("dos", 7));
    printnode(push("dos", 8));

/*
    printf("Eliminamos:\n");
    printnode(pop("uno"));
    printnode(pop("uno"));
    printnode(pop("uno"));
    printnode(pop("uno"));
    printnode(pop("uno"));
    printnode(pop("uno"));
    printnode(pop("dos"));
    printnode(pop("dos"));
    printnode(pop("dos"));
    printnode(pop("dos"));
*/
    printdictionary();
    freedictionary();

}

