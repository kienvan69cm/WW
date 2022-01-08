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
struct Progress
{
    int employeeID;
    int progressID;
    float progress;
};
void getEmployees(struct Employee *Employees, int *n)
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
        token[strlen(token) - 1] = '\0';
        strcpy(Employees[i].country, token);
        i++;
    }
    *n = i;
    fclose(fpt);
}
void getProgress(struct Progress *Progresses, int *m)
{
    FILE *fpt;
    char str[MAXCHAR];
    int i = 0;
    fpt = fopen("Progress.csv", "r");
    fgets(str, MAXCHAR, fpt);
    while (fgets(str, MAXCHAR, fpt))
    {
        char *token;
        token = strtok(str, ",");
        Progresses[i].employeeID = atoi(token);
        token = strtok(NULL, ",");
        Progresses[i].progressID = atoi(token);
        token = strtok(NULL, ",");
        Progresses[i].progress = atof(token);
        i++;
    }
    *m = i;
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
    fprintf(fpt, "%d,%s,%s,%s,%s,%d,%s\n", Employee.ID, Employee.firstName, Employee.lastName, Employee.gender, Employee.birthDay, Employee.department, Employee.country);
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
void report(struct Progress *Progresses, int m, float n)
{
    FILE *fpt;
    fpt = fopen("result.csv", "w");
    for (int i = 0; i < m; i++)
    {
        if (n == Progresses[i].progress)
            fprintf(fpt, "%d\n", Progresses[i].employeeID);
    }
    fclose(fpt);
}
void average(struct Progress *Progresses, int m, int x)
{
    FILE *fpt;
    float sum = 0;
    int count = 0;
    fpt = fopen("result.csv", "w");
    for (int i = 0; i < m; i++)
    {
        if (x == Progresses[i].progressID)
        {
            sum += Progresses[i].progress;
            count++;
        }
    }
    float avg = 0;
    if (count != 0)
        avg = sum / count;
    fprintf(fpt, "%.3f\n", avg);
    fclose(fpt);
}
void sort(struct Employee *Employees, int n, char *order)
{
    FILE *fpt;
    fpt = fopen("result.csv", "w");
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(Employees[i].lastName, Employees[j].lastName) > 0)
            {
                struct Employee tmp = Employees[i];
                Employees[i] = Employees[j];
                Employees[j] = tmp;
            }
            else if (strcmp(Employees[i].lastName, Employees[j].lastName) == 0)
            {
                if (strcmp(Employees[i].firstName, Employees[j].firstName) > 0)
                {
                    struct Employee tmp = Employees[i];
                    Employees[i] = Employees[j];
                    Employees[j] = tmp;
                }
            }
        }
    }
    if (strcmp(order, "asc") == 0)
    {
        for (int i = 0; i < n; i++)
        {
            printEmployee(fpt, Employees[i]);
        }
    }
    else if (strcmp(order, "desc") == 0)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            printEmployee(fpt, Employees[i]);
        }
    }
}
void country(struct Employee *Employees, int n, char *country)
{
    FILE *fpt;
    fpt = fopen("result.csv", "w");
    for (int i = 0; i < n; i++)
    {
        if (strcmpi(Employees[i].country, country) == 0)
            printEmployee(fpt, Employees[i]);
    }
    fclose(fpt);
}
void wrongSyntax()
{
    FILE *fpt;
    fpt = fopen("check.txt", "w");
    fprintf(fpt, "wrong syntax");
}
int main(void)
{
    struct Employee Employees[1000];
    struct Progress Progresses[1000];
    int n;
    int m;
    getEmployees(Employees, &n);
    getProgress(Progresses, &m);
    char request[MAXCHAR];
    gets(request);
    char *func;
    char *para;
    char *token = strtok(request, " ");
    func = strlwr(token);
    token = strtok(NULL, " ");
    para = strlwr(token);
    token = strtok(NULL, " ");
    if (token != NULL || para == NULL)
        wrongSyntax();
    else
    {
        if (strcmp(func, "count") == 0)
        {
            count(Employees, n, atoi(para));
        }
        else if (strcmp(func, "list") == 0)
        {
            if (strcmp(para, "male") == 0)
                list(Employees, n, "male");
            else if (strcmp(para, "female") == 0)
                list(Employees, n, "female");
            else
                wrongSyntax();
        }
        else if (strcmp(func, "report") == 0)
        {
            if (atof(para) > 0 && atof(para) <= 1)
                report(Progresses, m, atof(para));
            else
                wrongSyntax();
        }
        else if (strcmp(func, "average") == 0)
            average(Progresses, m, atoi(para));
        else if (strcmp(func, "sort") == 0)
        {
            if (strcmp(para, "asc") == 0)
                sort(Employees, n, "asc");
            else if (strcmp(para, "desc") == 0)
                sort(Employees, n, "desc");
            else
                wrongSyntax();
        }
        else if (strcmp(func, "country") == 0)
            country(Employees, n, para);
        else
            wrongSyntax();
    }
    return 0;
}