/*
*
*Author: Rakesh Malepu
*       Embedded Software Developer
*
*Date   : 22/10/2019
*
*/
#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include <windows.h>
#include <stdio.h>
#include <conio.h>

typedef enum{NO_FILE = -1,ACCESS = 1,NO_EMP = -1,BACK = 0}status;
typedef enum{LOG_IN = 0,CHECK , CHECKP}emp;
typedef enum{EMPL = 1, ADMN}desig;
extern char name[20];
extern char pswd[20];

void wait(void);
#endif // COMMON_H_INCLUDED
