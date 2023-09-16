#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <signal.h>

#define MAX_BUFFER_SIZE 1024 /* max size of the buffer */
#define BUFFER_FLUSH_CONDITION -1 /* the condition when we flush */
#define MAX_ARGS 10
#define IS_UNSIGNED 1
#define IS_LOWERCASE 2
#define HISTORY_FILE ".simple_shell_history"
#define AND_COMMAND 5
#define OR_COMMAND 6
#define CHAIN_COMMAND 7
#define NORM_COMMAND 0

extern char **environ;

typedef struct myNewList
{
	int theNum;
	char *myString;
	struct myNewList *next;
} myList;

/**
 * struct pass_inf - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @argument: a string generated from getline containing arguments
 * @arguments: an array of strings generated from argument
 * @path: a string path for the current command
 * @argument_count: the argument count
 * @line_count: the error count
 * @error_number: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @filename: the program filename
 * @environment: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @environ: custom modified copy of environ from LL env
 * @environment_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @command_buffer: address of pointer to command buffer, on if chaining
 * @command_buffer_type: command type ||, &&, ;
 * @read_file_descriptor: the file descriptor from which to read line input
 * @history_count: the history line number count
 */
typedef struct pass_inf
{
	char *argument;
	char **arguments;
	char *path;
	int argument_count;
	unsigned int line_count;
	int error_number;
	int linecount_flag;
	char *filename;
	myList *environment;
	myList *history;
	myList *alias;
	char **environ;
	int environment_changed;
	int status;

	char **command_buffer;
	int command_buffer_type;
	int read_file_descriptor;
	int history_count;
} myInfoObject;

#define Iintializing_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL,\
NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/*string_function_1*/
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_strcat(char *str1, const char *str2);
char *_strcpy(char *str1, char *str2);
char *_strncpy(char *str1, char *str2, int n);

/*string_functions_2*/
char *_strdup(char *str);
char *startsWith(const char *myString, const char *theSString);
char *_memset(char *s, char b, unsigned int n);
char *_strchr(const char *myString, char myChar);

/*string_functions_3*/
char *_strncat(char *dest, char *src, int n);
void _puts(char *s);
int _putchar(char c);

/*memory_functions_1*/
char *_memset(char *s, char b, unsigned int n);
void freeAString(char **myPointer);
bool freeNulling(char **myPointer);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*additional_functions_1*/
bool isInteractive(myInfoObject *myInfo);
bool _isalpha(int myChar);
bool isDelim(char checkedOne, char *theStringDel);
int _atoi(char *s);

/*errors functions*/
int put_fd(char c, int file_descriptor);
int _puts_fd(char *string, int file_descriptor);
void printingErros(myInfoObject *myInfo, char *myError);

/*enviroment functions 1*/
int printingEnviormentList(myInfoObject *myInfo);
char *gettingEnviormentVariable(myInfoObject *myInfo, const char *myRVar);
int preparnigForSettingEnv(myInfoObject *myInfo);
int preparingForUnsettingEnv(myInfoObject *myInfo);
int makingtheLinkedList(myInfoObject *myInfo);

/*enviorment functions 2*/
char **gettingMyEnviron(myInfoObject *myInfo);
int unsetEnvVar(myInfoObject *myInfo, char *myVar);
int settingEnvVar(myInfoObject *myInfo, char *myVar, char *myValue);

/*commanding and path functions*/
bool isExecutable(__attribute__((unused)) myInfoObject *myP, char *FaresPath);
char *duplicatingMyChars(char *myPathStr, int myStart, int myEnd);

/*myInfo object functions*/
void clearMyInfoVariable(myInfoObject *myInfo);
void settingMyInfoVariable(myInfoObject *myInfo, char **myArgv);

/*some more functions*/
char *convertor(long int num, int myBase, int myFlags);
void removingComments(char *myBuffer);
int errorToInteger(char *myError);

/*linked list functions part 1*/
size_t print_list(const myList *h);
myList *addingNodeBeg(myList **myHead, const char *myString, int num);
myList *add_node_end(myList **head, const char *str, int num);
void free_list(myList **head);

/*linked list functions part 2*/
size_t linkedListLength(myList *myHead);
size_t printingTheList(const myList *myHead);
size_t gettingTheIndex(myList *myHead, myList *theRequiredNode);
myList *isNodeStartsWith(myList *myHead, char *theSearchPre, char afterChar);

/*builtin Ass functions part 1*/
int _exit_shell(myInfoObject *myInfo);
int _cd_(myInfoObject *myInfo);
int _help_(myInfoObject *take_in_your_ass);

/*builtin Ass functions part 2*/
int print_history(myInfoObject *game_of_thrones);
int _unset_alias(myInfoObject *die, char *dying);
int _set_alias(myInfoObject *help, char *me);
int man_alias(myInfoObject *myInfo);

/* geline */
void handle_sigin(__attribute__((unused))int empty);
int _getline(myInfoObject *myInfo, char **lineptr, size_t *n);
ssize_t ReadBuffer(myInfoObject *myInfo, char *buffer, size_t *i);
ssize_t GetInput(myInfoObject *myInfo);
ssize_t InputBuffer(myInfoObject *myInfo, char **buffer, size_t *length);
/*
	----------------
	Not finished Yet -> To be continued
	----------------
*/
#endif
