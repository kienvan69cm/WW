#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char *name;
    gets(name);
    printf(strlwr(name));
    return 0;
}