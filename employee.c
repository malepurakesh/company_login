/*
*
*Author: Rakesh Malepu
*       Embedded Software Developer
*
*Date   : 22/10/2019
*
*/
#include <stdlib.h>
#include <string.h>
#include "common.h"
extern int change_pswd(int desig);
extern char *readPassword();
void readDiary(void);
char name[20];
char pswd[20];
char diary_name[24];
void writeDiary(void);
char *diaryName(void);

/*
*This function contains the menu in the Employee profile
*/
void employee(void)
{
    char ch;
up:
    system("cls");
    printf("\n\n\n\t\t\tEmployee Profile<%s>",name);
    printf("\n\n\n\t\ta.Write Employee Diary");
    printf("\n\t\tb.Read Employee Diary");
    printf("\n\t\tc.Change the Password");
    printf("\n\t\td.Log out\n");
    while(1)
    {
        ch = getch();
        if(ch == 'a')
        {
            system("cls");
            writeDiary();
            goto up;
        }
        else if(ch =='b')
        {
            system("cls");
            readDiary();
            goto up;
        }
        else if(ch == 'c')
        {
            if(change_pswd(EMPL) == 1)
            {
                printf("\n\n\t\t\t OK");
            }
            else
            {
                printf("\n\n\t\t\tNot OK");
            }
            Sleep(1000);
            goto up;
        }
        else if(ch == 'd')
        {
            printf("\n\n\t\tLogging out.......... :-)\n");
            Sleep(1000);
            break;
        }
    }
}

/*
*This is the function for multi purpose
*Log in for admin
* Log in for Employee
*To check an Employee exist in database or not
*To change the password
*/
int employee_login_and_check(int task, int desig)
{
    FILE *fp;
    int len = 0;
    int name_temp = 0;
    int cur_pos = 0;
    int pass_temp = 0;
    char ch;
    char uname[20];
    char pass[20];
again:
    len = name_temp = cur_pos = pass_temp = 0;
    if(task == LOG_IN)
    {
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t\t Login");
        printf("\n\n\t\tUser Name:");
        scanf("%s",uname);
        printf("\n\t\tPassword:");
        sprintf(pass, "%s", readPassword());
    }
    else if(task == CHECK)
    {
        system("cls");
        printf("\n\n\n\n\n\t\t\tEmployee Check\n");
        printf("\n\n\t\tEnter Name:");
        scanf("%s",uname);
    }
    if(desig == EMPL)
    {
        fp = fopen("employee.txt","r");
    }
    else if(desig == ADMN)
    {
        fp = fopen("admin.txt","r");
    }
    if(fp == NULL)
    {
        printf("\n\n\t\t\tFile doesn't exist");
        Sleep(1000);
        return NO_FILE;
    }
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) == 0)
    {
        printf("\n\n\t\t ***********There is no data in the file*************");
        Sleep(1000);
        fclose(fp);
        return -1;
    }
    rewind(fp);
 check_again:
     len = strlen("Employee Name:");
    cur_pos = cur_pos + len;

    name_temp = cur_pos;
    fseek(fp, cur_pos, SEEK_SET);       //cursor locates before the name
    ch = fgetc(fp);
    while(ch != ' ')                    //while is used to move the cursor to end of the name in the file
    {
        ch = fgetc(fp);
    }
    cur_pos = ftell(fp);
    fseek(fp, name_temp, SEEK_SET);          //cursor locates before the name
    fgets(name,cur_pos-name_temp,fp);        //reads the name from the file  <temp>name<cur_pos>
    if(stricmp(uname, name) != 0)
    {
        if(desig == ADMN)
            {
                printf("\n\n\t\t*********No Employee with that Name*********\n");
                Sleep(1000);
                fclose(fp);
                return NO_EMP;
            }
        ch = fgetc(fp);
        while(ch != '\n')               //while is used to move the cursor to end of the line in the file
        {
            ch = fgetc(fp);
        }
        ch = fgetc(fp);                 //returns next line first character.....and cursor locates there
        if(ch == EOF)                   //End of the file
         {
             printf("\n\n\t\t*********No Employee with that Name*********\n");
             Sleep(1000);
             fclose(fp);
             return NO_EMP;
         }
         else                           //if the lines exists
         {
             cur_pos = ftell(fp);       //cursor at next line second  char
             cur_pos = cur_pos - 1;      //To make the cursor to locate the first character
             goto check_again;          //again checks the name in forward lines
         }
    }
    else
    {
        if(task == CHECK)
        {
            printf("\n\n\t\t*********Employee exists with that Name*********\n");
            Sleep(1000);
            fclose(fp);
            len = name_temp - len;
            return len;
        }
        len = strlen("Conf:");
        pass_temp = cur_pos + len;      //variable to store the location of before name
        fseek(fp, len, SEEK_CUR);       //moving the cursor forward of length of string(conf:)
        ch = fgetc(fp);
        while(ch != ' ')                //while is used to move the cursor to end of the password in the file
        {
            ch = fgetc(fp);
        }
        cur_pos = ftell(fp);            //cursor locates at the end of password(space)
        fseek(fp, pass_temp-cur_pos, SEEK_CUR);      //move the cursor to before the password in the file   fseek(fp,-len of pass, SEEK_CUR);
        fgets(pswd, cur_pos - pass_temp, fp);        //store the password in a variable
        if(strcmp(pass, pswd) == 0)
        {
            fclose(fp);
            printf("\n\n\n\t\tAccess Ok\n");
            Sleep(1000);
            return ACCESS;
        }
        else
        {
         printf("\n\n\n\t\tWrong Password");
         printf("\n\n\t\tTo try again enter 't' / To go back enter 'b'\n");
         ch = getch();
         while(1)
         {
             if (ch == 't')
             {
                 fclose(fp);
                 goto again;
             }
             else if(ch == 'b')
             {
                 fclose(fp);
                 printf("\n\n\t\tMoving Back.......... :-)\n");
                 Sleep(1000);
                 return BACK;
             }
             ch = getch();
         }
        }
    }
    fclose(fp);
}

/*
*This function is to generate a name with .txt extension
*/
char *diaryName(void)
{
    memcpy(diary_name,name,sizeof(name));
    strcat(diary_name,".txt");
    return diary_name;
}

/*
* This function is to read an Employee his diary
*/
void readDiary(void)
{
    FILE *fp;
    char ch;

    fp = fopen(diaryName(),"r");
    if(fp == NULL)
    {
        printf("\n\n\t\tFile Not Exist\n");
        fclose(fp);
        Sleep(1000);
    }
    else
    {
        printf("\n\n\t\tData in the file\n\n");
        ch = fgetc(fp);
        while(ch != EOF)
        {
            printf("%c",ch);
            ch = fgetc(fp);
        }
        fclose(fp);
        printf("\n\n\t\t\t\t\t\tb.Back\n");
        wait();
    }
}

/*
*This function is to facilitate an Employee to write his diary
*/
void writeDiary(void)
{
    FILE *fp;
    char buf[100];
    char ch;
    fp = fopen(diaryName(), "a");
again:
    printf("\n\t\t You can Write only 100 characters once\n");
    printf("\t Enter the matter:\n");
    scanf("\n");
    fgets(buf, sizeof(buf), stdin);
    fputs(buf,fp);
    printf("\n\t\tSaved.........!");
    printf("\n\tDo You want to write more........?");
    printf("\n\t1.y");
    printf("\n\t2.n");
    while(1)
    {
        ch = getch();
        if(ch == 'y' || ch == '1')
        {
            goto again;
        }
        else if(ch == 'n' || ch == '2')
        {
             fclose(fp);
             return ;
        }
    }
}
