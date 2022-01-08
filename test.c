#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000
struct Employee
{
    char ID[8];
    char firstName[15];
    char lastName[15];
    char gender[7];
    char birthDay[11];
    char department[6];
    char country[20];
};
void getinput(struct Employee *Employees, int *n)
{
    FILE *file;
    char str[MAXCHAR];
    file = fopen("Employee.csv", "r");
    int i = 0;
    fgets(str, MAXCHAR, file);
    while (fgets(str, MAXCHAR, file))
    {
        char *token;
        token = strtok(str, ",");
        strcpy(Employees[i].ID, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].firstName, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].lastName, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].gender, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].birthDay, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].department, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].country, token);
        i++;
    }
    *n = i;
    fclose(file);
}
void count(struct Employee *Employees, int n, char department[])
{
    FILE *file;
    file = fopen("result.csv", "w");
    int c = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(Employees[i].department, department) == 0)
        {
            c++;
        }
    }
    fprintf(file, "%d", c);
    fclose(file);
}
int main(void)
{
    struct Employee Employees[MAXCHAR];
    int n;
    char department[6];
    getinput(Employees, &n);
    printf("Nhap ma bo phan: ");
    scanf("%s", &department);
    count(Employees, n, department);
    return 0;
}
