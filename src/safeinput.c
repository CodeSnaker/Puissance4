#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "safeinput.h"


void flushbuff() // Inspire du cours sur le langage c sur OpenClassroom par Mathieu Nebra
{
    int c;
    while((c = getchar()) != EOF && c != '\n')
    {
        //getchar() gets every character in the stdin buffer 
    }
}


int readfile(char *stringArr, int limit, FILE *file) 
{
    char *newlinePoint=NULL;
    if(fgets(stringArr, limit+1, file) != NULL)
    {
        newlinePoint=strchr(stringArr, '\n');
        if(newlinePoint != NULL) {
            *newlinePoint = '\0';
        }
        else 
        {
            printf( "Error : buffer too small ");
            return 0;
        }
        return 1;
    }
    else 
    {
        printf("Error : couldn't read file line");
        return 0;
    }
}

int reads(char *stringArr, int limit) // Inspire du cours sur le langage c sur OpenClassroom par Mathieu Nebra
{
    char *newlinePoint=NULL;
    if(fgets(stringArr, limit+1, stdin) != NULL)
    {
        newlinePoint=strchr(stringArr, '\n');
        if(newlinePoint != NULL) {
            *newlinePoint = '\0';
        }
        else 
        {
            flushbuff();
        }
        return 1;
    }
    else 
    {
        flushbuff();
        return 0;
    }
}


long readstol(char *stringArr, int limit) 
{
    if(reads(stringArr, limit)) return strtol(stringArr, NULL, 10);
    else return 0;
}


double readstod(char *stringArr, int limit) 
{
    if (reads(stringArr, limit)) return strtod(stringArr, NULL);
    else return 0;
}


int strisnumber(char *stringArr) {
    for (int i=0; i<strlen(stringArr); i++)
    {
        if(!isdigit(stringArr[i])) return 0;
    }
    return 1;
}


int strisdouble(char *stringArr) {
    int decPoint=0;
    for (int i=0; i<strlen(stringArr); i++)
    {
        if(!isdigit(stringArr[i])) 
        {
            switch (stringArr[i])
            {
                case '.':
                    ++decPoint;
                    if (decPoint > 1) return 0;
                    break;
                
                default:
                    return 0;
            }
            
        }
    }
    return 1;
}