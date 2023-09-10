#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024 /* max size of the buffer */
#define BUFFER_FLUSH_CONDITION -1 /* the condition when we flush */


typedef struct myNewList
{
	int theNum;
	char *myString;
	struct myNewList *next;
} myList;

/*string_function_1*/
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_strcat(char *str1, const char *str2);
char *_strcpy(char *str1, char *str2);
char *_strncpy(char *str1, char *str2, int n);

/*string_functions_2*/
char *_strdup(char *str);
char *startsWith(const char *myString, const char *theSString);
<<<<<<< HEAD
char *_memset(char *s, char b, unsigned int n);
=======
>>>>>>> 21de96d24a8f3f3fa61ef5c75a5775b18ced5946
char *_strchr(const char *myString, char myChar);

/*string_functions_3*/
char *_strncat(char *dest, char *src, int n);
void _puts(char *s);
int _putchar(char c);

/*memory_functions_1*/
char *_memset(char *s, char b, unsigned int n);
void freeAString(char **myPointer);
bool freeNulling(char **myPoitner);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*additional_functions_1*/
bool isInteractive(myInfoObject *myInfo);
bool _isalpha(int myChar);
bool isDelim(char checkedOne, char *theStringDel);
int _atoi(char *s);


#endif
