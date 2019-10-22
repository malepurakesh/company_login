/*
*
*Author: Rakesh Malepu
*       Embedded Software Developer
*
*Date   : 22/10/2019
*
*/
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "common.h"
extern void dev_home(void);
extern void admin(void);
extern int admin_login(void);
extern int employee_login_and_check(int task, int desig);
extern void employee(void);

/*At first time the default user name and password of admin */
void admin_default(void)
{
    FILE *fp;
    fp = fopen("admin.txt","r");
    if(fp == NULL)
    {
        fp = fopen("admin.txt","w");
        fputs("Employee Name:admin Conf:devsys confidentials",fp);
        fclose(fp);
    }
    fclose(fp);

}
/*
*This is the main function of the application
*/
int main()
{
    char ch;
    admin_default();
up:
    system("cls");
    printf("\n\n\n\n\n\t\t\tDevSys Embedded Technologies");
    printf("\n\n\n\t\ta.Home");
    printf("\n\t\tb.Admin Log in");
    printf("\n\t\tc.Employee Log in");
    printf("\n\t\td.About Application");
    printf("\n\n\n\n\t\t\t\t\t\te.Exit\n");

    while(1)
    {
        ch = getch();
        switch(ch)
        {
        case 'a':
            dev_home();
            goto up;
        case 'b':
            if(employee_login_and_check(LOG_IN, ADMN) == ACCESS)
            {
                printf("\n\n\t\t\t\tMoving to your page...... :-)\n");
                Sleep(1000);
                admin();
                goto up;
            }
            else
            {
                goto up;
            }
        case 'c':
            if(employee_login_and_check(LOG_IN, EMPL) == ACCESS)
            {
                printf("\n\n\t\t\t\tMoving to your page...... :-)\n");
                Sleep(1000);
                employee();
                goto up;
            }
            else
            {
                goto up;
            }
            break;
        case 'd':
                system("cls");
                printf("\n\n\n\n\n\t\t\tAbout the application\n\n");
                printf("\n\t This application is of DevSys Embedded Technologies.\n\t Here the options about admin and employee login and \n\t home.In admin can insert the employee details and \n\t give the authentication access and employee list and\n\t employee check are present. In employee details login \n\t and diary with employee name. And some features have\n\t to implement, those are in admin removing of employee \n\t details and password change option. In employee have to\n\t implement change password option.\n\t\n\n\n\t\t*** Thank you ***");
                       printf("\n\n\n\t\t\t\t\t\t\tb.Back\n");
                   wait();
                   goto up;
        case 'e':
            printf("\n\nThe END\n\n");
            exit(0);
        }
    }
    return 0;
}

