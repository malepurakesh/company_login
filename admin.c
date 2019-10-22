#include <stdlib.h>
#include <string.h>
#include "common.h"
extern int change_pswd(int desig);
extern void wait(void);
extern int employee_login_and_check(int task, int desig);
void list();
void entry();
void remove_details();

/*
*This is the function to menu of admin profile
*/
void admin(void)
{
    char ch;
up:
    system("cls");
    printf("\n\n\n\t\t\tAdmin Profile");
    printf("\n\n\n\t\td.Entry Employee Details");
    printf("\n\t\te.Remove Employee Details");
    printf("\n\t\tf.Employee List");
    printf("\n\t\tg.Employee Check");
    printf("\n\t\th.Change Password");
    printf("\n\t\ti.Log out\n");
    while(1)
    {
        ch = getch();
        if(ch == 'd')
        {
            system("cls");
            entry();
            goto up;
        }
        else if(ch == 'e')
        {
            remove_details();
            goto up;
        }
        else if(ch == 'f')
        {
            system("cls");
            list();
            goto up;
        }
        else if(ch == 'g')
        {
            employee_login_and_check(CHECK, EMPL);
            goto up;
        }
        else if(ch == 'h')
        {
            if (change_pswd(ADMN) == 1)
                printf("\n\n\t\t\t OK");
            else
                printf("\n\n\t\t\t Not ok");
            Sleep(1000);
            goto up;
        }
        else if(ch == 'i')
         {
             printf("\n\n\t\tLogging out.......... :-)\n");
             Sleep(1000);
             break;
        }
    }
}

/*
*This is the function to make the admin to entry the Employee details
*/
void entry()
{
    char name[20];
    int id;
    FILE *fle;
    fle = fopen("employee.txt", "a");
    printf("\n\n\n\t\t\tEntry of Employee Details\n");
    printf("\n\n\t\tEmployee Name:");
    scanf("%s",name);
    fprintf(fle,"Employee Name:%s ",name);
    printf("\n\n\t\tAccess Password:");
    scanf("%s",name);
    fprintf(fle,"Conf:%s ",name);
    printf("\n\t\tEmployee ID:");
    scanf("%d",&id);
    fprintf(fle,"Employee ID:%d",id);
    fputs("\n",fle);
    fclose(fle);
    //list();
}

/*
*This is the function to make the admin to remove the Employee details
*/
void remove_details()
{
    FILE *fp;
    FILE *temp_fp;
    char ch;
    int check;
    long int len = 0;

    check = employee_login_and_check(CHECK, EMPL);
    fp = fopen("employee.txt","r");
    temp_fp = fopen("temp.txt","w");
    if(check > 0)
    {
        rewind(temp_fp);
        while(len < check)
        {
            ch = fgetc(fp);
            fputc(ch,temp_fp);
            len = ftell(fp);
        }
        fseek(fp, check, SEEK_SET);
        ch = fgetc(fp);
        while(ch != '\n')
        {
            ch = fgetc(fp);
        }
        ch = fgetc(fp);
        while(ch != EOF)
        {
            fputc(ch,temp_fp);
            ch = fgetc(fp);
        }
        fclose(fp);
        fclose(temp_fp);
        remove("employee.txt");
        if(rename("temp.txt", "employee.txt") == 0)
            printf("\n\n\t\t\tDone");
        else
            printf("\n\n\t\t\tNot done");

        printf("\n\n\t\t*********Details removed Successfully*********\n");
        Sleep(1000);
    }
    else if(check == 0)
    {
        ch = fgetc(fp);
        while(ch != '\n')
        {
            ch = fgetc(fp);
        }
        while(1)
        {
            ch = fgetc(fp);
            if(ch == EOF)
                break;
            printf("%c",ch);
            fputc(ch, temp_fp);
        }
        fclose(fp);
        fclose(temp_fp);
        remove("employee.txt");
        if(rename("temp.txt", "employee.txt") == 0)
            printf("\n\n\t\t\tDone");
        else
            printf("\n\n\t\t\tNot done");

        printf("\n\n\t\t*********Details removed Successfully*********\n");
        Sleep(3000);
    }
    else if (check == -1)
    {
        fclose(fp);
        fclose(temp_fp);
        Sleep(1000);
    }
}

/*
*This is the function to print the list of Employees
*/
void list()
{
    char ch;
    FILE *fle;
    printf("\n\t\tEmployee List\t\t\n\n\n");
    fle = fopen("employee.txt", "r");
    ch = fgetc(fle);
    while(ch != EOF)
    {
        printf("%c",ch);
        ch = fgetc(fle);
    }
    printf("\n\n\n\n\t\t\t\t\t\tb.Back");
    wait();
    fclose(fle);
}

