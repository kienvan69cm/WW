#include <stdio.h>
#define MAXCHAR 1000
int main(void)
{
    FILE *fpt;
    char c, d;
    char str[MAXCHAR];
    char *token;
    fpt = fopen("Employee.csv", "r");
    while (fgets(str, MAXCHAR, fpt))
    {
        puts(str);
        token = strtok(str, ",");

        while (token != NULL)
        {
            printf("Token: %s\n", token);
            token = strtok(NULL, ",");
        }
    }
    fclose(fpt);
    return 0;
}