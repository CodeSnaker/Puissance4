#ifndef SAFEINPUT_H_INCLUDED
#define SAFEINPUT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief flushes stdin buffer
 * * if you use this, make sure that there ARE characters in the buffer, else it will create weird behaviors
 */
void flushbuff(); // Inspire du cours sur le langage c sur OpenClassroom par Mathieu Nebra

/**
 * @brief reads a line from a file and replaces the newline caracter by '\0'
 * 
 * @param stringArr buffer which stores the line
 * @param limit max caracter that readfile can read
 * @param file pointer to FILE
 * @return int 
 */
int readfile(char *stringArr, int limit, FILE *file);

/**
 * @brief reads a line from stdin stream, replaces '\n' with '\0' and flushes input buffer
 * returns 1 if successful, 0 if not
 * @param stringArr is a string pointer in which the line is stored
 * @param limit is the limit of character that the function will read
 * ! stringArr must have space to store the characters '\0' at the end of the string
 * @return int 
 */
int reads(char *stringArr, int limit); // Inspire du cours sur le langage c sur OpenClassroom par Mathieu Nebra

/**
 * @brief turns the reads function's result into a long int
 * returns 0 if unsuccessful
 * @param stringArr is a string pointer in which the line is stored
 * @param limit is the limit of character that the function will read
 * @return long 
 */
long readstol(char *stringArr, int limit);

/**
 * @brief turns the reads function's result into a double
 * returns 0 if unsuccessful
 * @param stringArr is a string pointer in which the line is stored
 * @param limit is the limit of character that the function will read
 * @return double 
 */
double readstod(char *stringArr, int limit);

/**
 * @brief determines if the string contains only numbers
 * returns 1 if true, 0 if false
 * @param stringArr is the char* pointer which contains the string
 * @return int 
 */
int strisnumber(char *stringArr);

/**
 * @brief determines if the string is a double (contains only numbers and eventually one decimal point)
 * returns 1 if true, 0 if false
 * @param stringArr is the char* pointer which contains the string
 * @return int 
 */
int strisdouble(char *stringArr);

#endif