#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024 /* max size of the buffer */
#define BUFFER_FLUSH_CONDITION -1 /* the condition when we flush */

/*string_function_1*/
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_strcat(char *str1, const char *str2);
char *_strcpy(char *str1, char *str2);
char *_strncpy(char *str1, char *str2, int n);

/*string_functions_3*/
char *_strncat(char *dest, char *src, int n);
void _puts(char *s);
int _putchar(char c);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);



#endif
