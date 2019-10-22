#include "common.h"
extern int employee_login_and_check(int task, int desig);
char * exchange(char * buf, char *name, char * replace);
char *readPassword();
char psnm[10] = {0};

/*
*This is the function to wait till getting the break command
*/
void wait(void)
{
    char ch;
    while(1)
    {
        ch = getch();
        if(ch == 'b' || ch == 'B')
            break;
    }
}

/*
*This is the function to change the password of Admin and Employee also
*/
int change_pswd(int desig)
{
    FILE *fp;
    FILE *temp;
    char nme[10];
    int check = 0;
    int check1 = 0;
    int i = 0;
    char ch = NULL;
    char buf[100] = {0};
    char buf2[100] = {0};

    if(desig == EMPL)
    {
        fp = fopen("employee.txt","r");
        temp = fopen("temp.txt","w");
    }
    else if(desig == ADMN)
    {
        fp = fopen("admin.txt","r");
        temp = fopen("temp.txt","w");
    }
    check = employee_login_and_check(CHECK,desig);
    if(check == -1 )
    {
        fclose(fp);
        fclose(temp);
        return 0;
    }
    else if(check >= 0)
    {
        fseek(fp, check, SEEK_SET);

        ch = fgetc(fp);
        if(desig == ADMN)
        {
            while(ch != EOF)
            {
                ch = fgetc(fp);
            }
        }
        else
            {
                while(ch != '\n')
                {
                    ch = fgetc(fp);
                }
            }
        check1 = ftell(fp);
        fseek(fp, check, SEEK_SET);
        fgets(buf,check1 - check, fp);
        printf("\n\n\t\t Enter new Password less than 10 char's:");
        sprintf(nme, "%s", readPassword());
        sprintf(buf2,"%s",exchange(buf,nme,pswd));
        rewind(fp);
        ch = fgetc(fp);
        printf("\n\n");
        while(ftell(fp) <= check)
        {
            fputc(ch,temp);
            ch = fgetc(fp);
        }
        i=0;
        while(i< strlen(buf2))
        {
            fputc(buf2[i],temp);
            i++;
        }
        fseek(fp, check1, SEEK_SET);
        ch = fgetc(fp);
        while(ch != EOF)
        {
            fputc(ch, temp);
            ch = fgetc(fp);
        }
        memset(buf,0,sizeof(buf));
        memset(buf2,0, sizeof(buf2));
        fclose(fp);
        fclose(temp);
        if(desig == EMPL)
        {
            remove("employee.txt");
            if(rename("temp.txt","employee.txt") == 0)
            {
                printf("\n\n\t\t\tDone");
            }
            else
                printf("\n\t\t\tNot Done");
        }
        else if(desig == ADMN)
        {
            remove("admin.txt");
            rename("temp.txt", "admin.txt");
        }
        printf("\n\n\t\t\tChange done");
        Sleep(2000);
    }
    return 1;
}

/*
*This is the function to replace a word with another in a string
*/
char * exchange(char * buf, char *new_name, char *word_to_replace)
{
    int i = 0;
    int len = 0;
    char *ptr = NULL;
    char *buf2 = NULL;
    len = strlen(buf) - strlen(word_to_replace)+strlen(new_name);
    buf2 = (char *) realloc(buf2,len);
    ptr = strstr(buf, word_to_replace);
    len = strlen(buf) - strlen(ptr);
    while(i < len)
    {
        buf2[i] = buf[i];
        i++;
    }
    for (int j=0; j<strlen(new_name); j++)
    {
        buf2[i] = new_name[j];
        i++;
    }
    ptr = ptr + strlen(word_to_replace);
    while(*ptr != '\0')
    {
        buf2[i] = *ptr;
        *ptr++;
        i++;
    }
    buf2[i] = '\0';
    return buf2;
}

/*
*This is the function to read a string as password (printing *'s instead of char's)
*/
char *readPassword()
{
    char ch;
    int i = 0;

    while(1)
    {
        ch = getch();
        if(ch == '\r')
            break;
        if(ch == '\b' || ch == '\t')
            continue;
        printf("*");
        psnm[i++] = ch;
    }
    psnm[i] = '\0';
    return psnm;
}
