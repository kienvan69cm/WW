#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000
struct Employee
{
    int ID;
    char firstName[15];
    char lastName[15];
    char gender[7];
    char birthDay[10];
    int department;
    char country[20];
};
void getInput(struct Employee *Employees, int *n)
{
    FILE *fpt;
    char str[MAXCHAR];
    int i = 0;
    fpt = fopen("Employee.csv", "r");
    fgets(str, MAXCHAR, fpt);
    while (fgets(str, MAXCHAR, fpt))
    {
        char *token;
        token = strtok(str, ",");
        Employees[i].ID = atoi(token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].firstName, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].lastName, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].gender, token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].birthDay, token);
        token = strtok(NULL, ",");
        Employees[i].department = atoi(token);
        token = strtok(NULL, ",");
        strcpy(Employees[i].country, token);
        i++;
    }
    *n = i;
    fclose(fpt);
}
void count(struct Employee *Employees, int n, int department)
{
    FILE *fpt;
    fpt = fopen("result.csv", "w");
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        if (Employees[i].department == department)
            c++;
    }
    fprintf(fpt, "%d", c);
    fclose(fpt);
}
void printEmployee(FILE *fpt, struct Employee Employee)
{
    fprintf(fpt, "%d,%s,%s,%s,%s,%d,%s", Employee.ID, Employee.firstName, Employee.lastName, Employee.gender, Employee.birthDay, Employee.department, Employee.country);
}
void list(struct Employee *Employees, int n, char *gender)
{
    FILE *fpt;
    fpt = fopen("result.csv", "w");
    if (gender == "male")
        gender = "Male";
    else if (gender == "female")
        gender = "Female";
    for (int i = 0; i < n; i++)
    {
        if (strcmp(Employees[i].gender, gender) == 0)
            printEmployee(fpt, Employees[i]);
    }
    fclose(fpt);
}
int main(void)
{

    struct Employee Employees[1000];
    int n;
    getInput(Employees, &n);
    list(Employees, n, "female");
    return 0;
}