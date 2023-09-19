#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
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
#define MAX_ALIASES_COUNT 15
extern char **environ;

/**
 * struct myNewList - A struct that makes a linked
 * list that makes my enviorment variables
 * @theNum: The number of the node
 * @myString: The string that is contained in the
 * node
 * @next: A pointer to the next node
*/

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

/**
 * struct builtinCommand - A struct that is created
 * to deal with the builtin commands and their names
 * @nameofFunction: A string that conatins the
 * name of the function
 * @myCommandFun: A pointer to a function
 * that its name matches with the previous member
*/

typedef struct builtinCommand
{
	char *nameofFunction;
	int (*myCommandFun)(myInfoObject *);
} myBuiltin;


#define Iintializing_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL,\
NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/*string_function_1*/
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *str1, char *str2);
char *_strncpy(char *str1, char *str2, int n);

/*string_functions_2*/
char *_strdup(char *str);
char *startsWith(const char *myString, const char *theSString);
char *_strchr(char *myString, char myChar);

/*string_functions_3*/
char *_strncat(char *dest, char *src, int n);
void _puts(char *s);
int _putchar(char c);

/*string functions 4*/
char **strtow(char *str, char *del);
char **strtow2(char *str, char *del);

/*memory_functions_1*/
char *_memset(char *s, char b, unsigned int n);
void freeAString(char **myPointer);
bool freeNulling(void **myPointer);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);

/*additional_functions_1*/
bool isInteractive(myInfoObject *myInfo);
bool _isalpha(int myChar);
int is_del(char c, char *del);
int _atoi(char *s);

/*errors functions*/
int put_fd(char c, int file_descriptor);
int _puts_fd(char *string, int file_descriptor);
void printingErrors(myInfoObject *myInfo, char *myError);
int _errorputchar(char myChar);
void _errorputschar(char *myString);

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
char *jOFP(myInfoObject *myInfo, char *pathEnvVar, char *myCommand);

/*myInfo object functions*/
void clearMyInfoVariable(myInfoObject *myInfo);
void settingMyInfoVariable(myInfoObject *myInfo, char **myArgv);
void freeMyInfo(myInfoObject *myInfo, int allCondition);

/*some more functions*/
char *convertor(long int num, int myBase, int myFlags);
void removingComments(char *myBuffer);
int errorToInteger(char *myError);
int printingDecimal(int myInput, int fileD);

/*linked list functions part 1*/
size_t print_list(const myList *h);
myList *addingNodeBeg(myList **myHead, char *myString, int num);
myList *add_node_end(myList **head, char *str, int num);
void free_list(myList **head);
int delete_node_at_index(myList **head, unsigned int index);

/*linked list functions part 2*/
size_t linkedListLength(myList *myHead);
size_t printingTheList(const myList *myHead);
size_t gettingTheIndex(myList *myHead, myList *theRequiredNode);
myList *isNodeStartsWith(myList *myHead, char *theSearchPre, char afterChar);
char **convertingNodeStringstoArray(myList *myHead);

/*builtin Ass functions part 1*/
int _exit_shell(myInfoObject *myInfo);
int _cd_(myInfoObject *myInfo);
int _help_(myInfoObject *take_in_your_ass);

/*builtin Ass functions part 2*/
int print_history(myInfoObject *game_of_thrones);
int _unset_alias(myInfoObject *die, char *dying);
int _set_alias(myInfoObject *help, char *me);
int PrintAlias(myList *pain);
int man_alias(myInfoObject *myInfo);

/* geline functions */
void handle_sigin(__attribute__((unused))int empty);
int _getline(myInfoObject *myInfo, char **lineptr, size_t *n);
ssize_t ReadBuffer(myInfoObject *myInfo, char *buffer, size_t *i);
ssize_t GetInput(myInfoObject *myInfo);
ssize_t InputBuffer(myInfoObject *myInfo, char **buffer, size_t *length);

/*chaining functions*/
bool isThereChaining(myInfoObject *myInfo, char *myBuffer, size_t *FaresPos);
void cSWC(myInfoObject *myI, char *myBuf, size_t *myPo, size_t i, size_t myL);
bool replacingMyAliases(myInfoObject *myInfo);
bool replacingMyVariables(myInfoObject *myInfo);
bool replacingNewandOldStrings(char **theOldOne, char *theNewOne);

/*history functions*/
char *GetHistoryFile(myInfoObject *myInfo);
int WriteHistory(myInfoObject *myInfo);
int ReadHistoryList(myInfoObject *myInfo);
int BuildHistoryList(myInfoObject *myInfo, char *buffer, int linecount);
int REM_History(myInfoObject *myInfo);

/*main function loop functions*/
int findingMyBuiltinFunc(myInfoObject *myInfo);
void forkingMyCmd(myInfoObject *myInfo);
void findingCommandLastTime(myInfoObject *myInfo);
int her_shell_hell(myInfoObject *shellInfo, char *arguments[]);

/*
 *	----------------
 *	Not finished Yet -> To be continued
 *	----------------
*/

#endif


/**
 * _exit_shell - it exits the damn shell
 * @myInfo: structure contains good information for easier use
 *
 * Return: -2 and exits the damn shell!
*/

int _exit_shell(myInfoObject *myInfo)
{
	int get_the_fuck_out_check;

	if (myInfo->arguments[1])
	{
		get_the_fuck_out_check = errorToInteger(myInfo->arguments[1]);
		if (get_the_fuck_out_check == -1)
		{
			myInfo->status = 2;
			printingErrors(myInfo, "Illegal number: ");
			_puts(myInfo->arguments[1]);
			_putchar('\n');
		}
		myInfo->error_number = errorToInteger(myInfo->arguments[1]);
		return (-2);
	}
	myInfo->error_number = -1;
	return (-2);
}

/**
 * _cd_ - it changes between directories
 * @myInfo: ..............
 *
 * Return: your mom is what it returns
*/

int _cd_(myInfoObject *myInfo)
{
	char *current_dir, *target_dir, FARES[1024];
	int cd_result;

	current_dir = getcwd(FARES, 1024);
	if (!current_dir)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
		return -1;
	}

	if (!myInfo->arguments[1])
	{
		target_dir = gettingEnviormentVariable(myInfo, "HOME=");
		if (!target_dir)
		{
			target_dir = "/";
			cd_result = chdir(target_dir);
		}
		else
		{
			cd_result = chdir(target_dir);
		}
	}
	else if (_strcmp(myInfo->arguments[1], "-") == 0)
	{
		target_dir = gettingEnviormentVariable(myInfo, "OLDPWD=");
		if (!target_dir)
		{
			_puts(current_dir);
			_putchar('\n');
			return 1;
		}
		else
		{
			_puts(target_dir);
			_putchar('\n');
			cd_result = chdir(target_dir);
		}
	}
	else
	{
		cd_result = chdir(myInfo->arguments[1]);
	}

	if (cd_result == -1)
	{
		printingErrors(myInfo, "can't cd to ");
		_puts(myInfo->arguments[1]);
		_putchar('\n');
		return -1;
	}
	else
	{
		settingEnvVar(myInfo, "OLDPWD", current_dir);
		settingEnvVar(myInfo, "PWD", getcwd(FARES, 1024));
		return 0;
	}
}

/**
 * _help_ - useless ass function
 * @take_in_your_ass: all of it
 *
 * Return: 0 like you size ;)
*/

int _help_(myInfoObject *take_in_your_ass)
{
	char **amr_alnas;

	amr_alnas = take_in_your_ass->arguments;
	_puts("IDK what to say here nyhahahaha but function not implemented");
	(void)amr_alnas;


	return (0);
}


/**
 * print_history - for real?
 * @game_of_thrones: good series
 *
 * Return: 0 after printing
*/
int print_history(myInfoObject *game_of_thrones)
{
	printingTheList(game_of_thrones->history);
	return (0);
}
/**
 * _unset_alias - it unsets an alias to be changed or whatever
 * @die: die
 * @dying: good
 *
 * Return: eminem
*/
int _unset_alias(myInfoObject *die, char *dying)
{
	int eminem;
	char *amr, fares;

	amr = _strchr(dying, '=');

	if (amr == NULL)
	return (1);

	fares = *amr;
	*amr = '\0';

	eminem = delete_node_at_index(&(die->alias),
		gettingTheIndex(die->alias, isNodeStartsWith(die->alias, dying, -1)));

	*amr = fares;

	return (eminem);
}
/**
 * _set_alias - -_-
 * @help: me for real.
 * @me: not him.
 *
 * Return: 1; otherwise, it returns 0.
*/
int _set_alias(myInfoObject *help, char *me)
{
	char *equal_sign, *alias_value;

	equal_sign = _strchr(me, '=');
	if (equal_sign == NULL)
	return (1);

	alias_value = equal_sign;
	alias_value++;

	if (!*alias_value)
	return (_unset_alias(help, me));

	_unset_alias(help, me);
	return (add_node_end(&(help->alias), me, 0) == NULL);
}
/**
 * PrintAlias - prints alias
 * @pain: good name
 *
 * Return: 0 on success, 1 on error.
*/
int PrintAlias(myList *pain)
{
	char *fares = NULL, *amr = NULL; /*as always my friend we are null :(*/

	if (!pain)
	return (1);

	fares = _strchr(pain->myString, '=');

	amr = pain->myString;
	while (amr <= fares)
	{
		_putchar(*amr);
		amr++;
	}
		_putchar('\'');
		_puts(fares + 1);
		_puts("'\n");
		return (0);
}
/**
 *man_alias - man alias and shit
 * @myInfo: f*ck off
 *
 * Return: zero.
*/
int man_alias(myInfoObject *myInfo)
{
		int i = 0;
	char *pain = NULL;
	myList *node = NULL;

	if (myInfo->argument_count == 1)
	{
		node = myInfo->alias;
		while (node)
		{
			PrintAlias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; myInfo->arguments[i]; i++)
	{
		pain = _strchr(myInfo->arguments[i], '=');
		if (pain)
			_set_alias(myInfo, myInfo->arguments[i]);
		else
			PrintAlias(isNodeStartsWith(myInfo->alias, myInfo->arguments[i], '='));
	}
	return (0);
}



/**
 * isThereChaining - A function to check if there is chaining in
 * the command or not
 * @myInfo: A variable that stores all the information about the
 * command
 * @myBuffer: A pointer to a string that stores the command
 * @FaresPos: The position in which we're searching for
 * a chaining
 *
 * Return: 0 on no chaining and 1 on there is chaning
*/

bool isThereChaining(myInfoObject *myInfo, char *myBuffer, size_t *FaresPos)
{
	int tempFarsePos = *FaresPos;
	bool isChaining = false;

	switch (myBuffer[tempFarsePos])
	{
		case '|':
			if (myBuffer[tempFarsePos + 1] == '|')
			{
				myBuffer[tempFarsePos] = '\0';
				tempFarsePos = tempFarsePos + 1;
				(*myInfo).command_buffer_type = OR_COMMAND;
				isChaining = true;
			}
			break;
		case '&':
			if (myBuffer[tempFarsePos + 1] == '&')
			{
				myBuffer[tempFarsePos] = '\0';
				tempFarsePos = tempFarsePos + 1;
				(*myInfo).command_buffer_type = AND_COMMAND;
				isChaining = true;
			}
			break;

		case ';':
			myBuffer[tempFarsePos] = '\0';
			(*myInfo).command_buffer_type = CHAIN_COMMAND;
			isChaining = true;
			break;
	}

	if (isChaining)
		*FaresPos = tempFarsePos;

	return (isChaining);
}

/**
 * cSWC - A function to check some conditions about || and &&
 * @myI: A pointer to myInfoObject variable that contains
 * everything about the shell currently
 * @myBuf: A pointer to a buffer
 * @myPo: A pointer that points to the place that
 * we're now on the command
 * @i: The beginning of the buffer
 * @myL: The length of the buffer
 *
 * Return: Nothing (void)
*/


void cSWC(myInfoObject *myI, char *myBuf, size_t *myPo, size_t i, size_t myL)
{
	size_t amrCounter = *myPo;

	if (myI->command_buffer_type == AND_COMMAND && myI->status)
	{
		myBuf[i] = '\0';
		amrCounter = myL;
	}
	else if (myI->command_buffer_type == OR_COMMAND && myI->status == 0)
	{
		myBuf[i] = '\0';
		amrCounter = myL;
	}

	*myPo = amrCounter;
}


/**
 * replacingMyAliases - A function to get my alias from the list
 * @myInfo: A pointer to myInfoObject that contains everything
 * about the shell
 *
 * Return: false on failure and true on success
*/

bool replacingMyAliases(myInfoObject *myInfo)
{
	int i;
	char *myPointer;
	myList *myHead;

	for (i = 0; i < MAX_ALIASES_COUNT; i++)
	{
		myHead = isNodeStartsWith((*myInfo).alias, (*myInfo).arguments[0], '=');
		if (myHead == NULL)
			return (false);
		free((*myInfo).arguments[0]);
		myPointer = _strchr((*myHead).myString, '=');
		if (myPointer == NULL)
			return (false);
		myPointer = _strdup(myPointer + 1);
		if (myPointer == NULL)
			return (false);
		(*myInfo).arguments[0] = myPointer;
	}
	return (true);
}

/**
 * replacingMyVariables - A function to replace variables that are
 * in my enviorment
 * @myInfo: A pointer to myInfoObject variable
 *
 * Return: 0 on success and 1 on failure
*/

bool replacingMyVariables(myInfoObject *myInfo)
{
	int i;
	myList *myHead;
	char *myPointer;

	for (i = 0; (*myInfo).arguments[i] != NULL; i++)
	{
		if ((*myInfo).arguments[i][0] != '$' ||
		(*myInfo).arguments[i][1] == '\0')
			continue;
			
		if (_strcmp((*myInfo).arguments[i], "$?") == 0)
		{
			myPointer = _strdup(convertor(
				(*myInfo).status, 10, 0));
			if (myPointer == NULL)
				return (true);
			replacingNewandOldStrings(&((*myInfo).arguments[i]), myPointer);
			continue;
		}
		else if (_strcmp((*myInfo).arguments[i], "$$") == 0)
		{
			myPointer = _strdup(convertor(
				getpid(), 10, 0));
			if (myPointer == NULL)
				return (true);
			replacingNewandOldStrings(&((*myInfo).arguments[i]), myPointer);
			continue;
		}
		myHead = isNodeStartsWith(myInfo->environment
		, &(myInfo->arguments[i][1]), '=');
		if (myHead != NULL)
		{
			myPointer = _strdup(_strchr((*myHead).myString, '=') + 1);
			if (myPointer == NULL)
				return (true);
			replacingNewandOldStrings(&((*myInfo).arguments[i]), myPointer);
			continue;
		}
		replacingNewandOldStrings(&((*myInfo).arguments[i]), "");
	}
	return (false);
}

/**
 * replacingNewandOldStrings - A function to replace strings
 * @theOldOne: A pointer to a pointer that points
 * to the old string
 * @theNewOne: A pointer that points to the new string
 *
 * Return: True
*/

bool replacingNewandOldStrings(char **theOldOne, char *theNewOne)
{
	free(*theOldOne);
	*theOldOne = theNewOne;
	return (true);
}



/**
 * isExecutable - A function to check if the file is executable or not
 * @myP: A Pointer to myInfoObject variable
 * and it's not used in this function
 * @FaresPath: The path to the file that we want to check
 *
 * Return: 0 on failling and 1 on success
*/

bool isExecutable(__attribute__((unused)) myInfoObject * myP, char *FaresPath)
{
	struct stat myStatVar;

	if (FaresPath == NULL || stat(FaresPath, &myStatVar))
		return (false);
	if (1) /*myStatVar.st_mode & S_IFREG*/
		return (true);
	return (false);
}

/**
 * duplicatingMyChars - A function to get sub-strings of
 * a path string
 * @myPathStr: A pointer to a string
 * that contains the path of a file
 * @myStart: The beginning of the path string
 * that we want to start exctracting from
 * @myEnd: The end of the path string
 * that we want to end the exctracting
 *
 * Return: A pointer to the buffer that contains
 * the sub-string
*/

char *duplicatingMyChars(char *myPathStr, int myStart, int myEnd)
{
	static char myBuffer[MAX_BUFFER_SIZE];
	int i = 0, bufferPos;

	for (bufferPos = 0, i = myStart; i < myEnd; i++)
	{
		if (myPathStr[i] != ':')
		{
			myBuffer[bufferPos] = myPathStr[i];
			bufferPos = bufferPos + 1;
		}
	}
	myBuffer[bufferPos] = '\0';
	return (myBuffer);
}


/**
 * jOFP - A function to find the path of the required command
 * @myInfo: A pointer to myInfoObject variable
 * @pathEnvVar: The PATH enviorment variable
 * @myCommand: The required command to be execuated
 *
 * Return: A pointer to the full path or NULL
*/

char *jOFP(myInfoObject *myInfo, char *pathEnvVar, char *myCommand)
{	/*journey of finding path*/
	int i = 0, myCurrentPos = 0;
	char *myEndPath;

	if (pathEnvVar == NULL)
		return (NULL);
	if ((_strlen(myCommand) > 2) && startsWith(myCommand, "./"))
	{
		if (isExecutable(myInfo, myCommand))
			return (myCommand);
	}
	while (true)
	{
		if (pathEnvVar[i] == '\0' || pathEnvVar[i] == ':')
		{
			myEndPath = duplicatingMyChars(pathEnvVar, myCurrentPos, i);
			if (myEndPath == NULL)
				_strcat(myEndPath, myCommand);
			else
			{
				_strcat(myEndPath, "/");
				_strcat(myEndPath, myCommand);
			}
			if (isExecutable(myInfo, myEndPath) == true)
				return (myEndPath);
			if (pathEnvVar[i] == '\0')
				break;
			myCurrentPos = i;
		}
		i = i + 1;
	}
	return (NULL);
}


/**
 * printingEnviormentList - A function to print the variables in the enviroment
 * @myInfo: A pointer to the enviorment linked list
 *
 * Return: Success or failure
*/

int printingEnviormentList(myInfoObject *myInfo)
{
	int theReturedValue = print_list((*myInfo).environment);

	return (theReturedValue);
}

/**
 * gettingEnviormentVariable - A function to get a pointer to
 * the enviroment varible that is stored in our linked list
 * @myInfo: A pointer to myInfo variable
 * @myRVar: A pointer to a string that we want to find
 * and this string represnts the enviorment variable that we want
 * to find
 *
 * Return: NULL or a pointer to node that cointains the required varible
*/

char *gettingEnviormentVariable(myInfoObject *myInfo, const char *myRVar)
{
	myList *myTempHead = (*myInfo).environment;
	char *myCP;

	while (myTempHead != NULL)
	{
		myCP = startsWith((*myTempHead).myString, myRVar);
		if (myCP != NULL && *myCP != '\0')
			return (myCP);
		myTempHead = (*myTempHead).next;
	}
	return (NULL);
}

/**
 * preparnigForSettingEnv - A function to prepare the setting enviorment
 * function to do its work
 * @myInfo: A pointer to info variable
 *
 * Return: 0 if success and 1 if failure
*/

int preparnigForSettingEnv(myInfoObject *myInfo)
{
	int sER;

	if ((*myInfo).argument_count != 3)
	{
		_puts_fd("Not correct number of arguments I think \n", 2); /*STDERR_FILENO*/
		return (1);
	}
	sER = settingEnvVar(myInfo, (*myInfo).arguments[1], (*myInfo).arguments[2]);
	return ((sER != 0) ? 1 : 0);
}

/**
 * preparingForUnsettingEnv - a function to prepare theunsetEnvVar function
 * to do its job
 * @myInfo: A pointer to myInfo varible that stores all the
 * information about the command inputed to the shell
 *
 * Return: 0 (Success) or 1 (Failure)
*/

int preparingForUnsettingEnv(myInfoObject *myInfo)
{
	int i = 0;

	if ((*myInfo).argument_count <= 1)
	{
		_puts_fd("Not correct number of arguments\n", 2); /*STDERR_FILENO*/
		return (1);
	}
	for (; i <= (*myInfo).argument_count; i++)
	{
		if (unsetEnvVar(myInfo, (*myInfo).arguments[i]) != 0)
			return (1);
	}
	return (0);
}
/**
 * makingtheLinkedList - A function to make the linked list
 * of enviorment variables
 * @myInfo: A pointer to info object that stores everything
 * about the command
 *
 * Return: 1 or 0
*/

int makingtheLinkedList(myInfoObject *myInfo)
{
	myList *listHead = NULL, *tempHead;
	size_t listSize = 0;

	for (; environ[listSize] != NULL; listSize++)
	{
		tempHead = add_node_end(&listHead, environ[listSize], 0);
		if (tempHead == NULL)
			return (1);
	}
	(*myInfo).environment = listHead;
	return (0);
}


/**
 * gettingMyEnviron - A function to make an array of strings
 * from the enviorment varibales that are in linked list
 * @myInfo: A pointer to myInfoObject that contains everything
 * about the command
 *
 * Return: A pointer to a pointer
*/

char **gettingMyEnviron(myInfoObject *myInfo)
{
	if ((*myInfo).environment_changed == 1 || (*myInfo).environ == NULL)
	{
		(*myInfo).environ = convertingNodeStringstoArray((*myInfo).environment);
		(*myInfo).environment_changed = 0;
	}
	return ((*myInfo).environ);
}

/**
 * unsetEnvVar - A function to unset a variable in the envirorment variables
 * @myInfo: A variable that stores everything about the commmand
 * @myVar: The name of the varibale to be deleted
 *
 * Return: It returns an integer that represents if we deleted a node or not
 * (It means if we have updated the linked list of enviorment or not)
*/

int unsetEnvVar(myInfoObject *myInfo, char *myVar)
{
	myList *myHead = (*myInfo).environment;
	size_t i = 0;
	char *myCP;

	if (myHead == NULL || myVar == NULL)
		return (0);
	while (myHead != NULL)
	{
		myCP = startsWith((*myHead).myString, myVar);
		if (myCP != NULL && *myCP == '=')
		{
			(*myInfo).environment_changed = delete_node_at_index(&(*myInfo).environment, i);
			i = 0;
			myHead = (*myInfo).environment;
			continue;
		}
		myHead = (*myHead).next;
		i++;
	}
	return ((*myInfo).environment_changed);
}

/**
 * settingEnvVar - A function to set an enviroment variable
 * in myInfo variable
 * @myInfo: A pointer to myInfo object
 * @myVar: The name of the variable that we want to set
 * @myValue: The value of the variable that we want to set
 *
 * Return: 1 on failure and 0 on success
*/

int settingEnvVar(myInfoObject *myInfo, char *myVar, char *myValue)
{
	char *myBuffer;
	myList *myHead;
	char *myCP;

	if (myVar == NULL || myValue == NULL)
		return (0);
	myBuffer = malloc(sizeof(myVar) + sizeof(myValue) + 2);
	_strcpy(myBuffer, myVar);
	_strcat(myBuffer, "=");
	_strcat(myBuffer, myValue);
	myHead = (*myInfo).environment;
	while (myHead != NULL)
	{
		myCP = startsWith((*myHead).myString, myVar);
		if (myCP != NULL && *myCP == '=')
		{
			free((*myHead).myString);
			_strcpy((*myHead).myString, myBuffer);
			(*myInfo).environment_changed = 1;
			free(myBuffer);
			return (0);
		}
		myHead = (*myHead).next;
	}
	add_node_end(&(*myInfo).environment, myBuffer, 0);
	free(myBuffer);
	(*myInfo).environment_changed = 1;
	return (0);
}


/**
 * handle_sigin - no ctrl+C
 * @empty: unused
 *
 * Return: nothing
*/
void handle_sigin(__attribute__((unused))int empty)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH_CONDITION);
}

/**
 * _getline - gets the line from standard input
 * @myInfo: I don't know man leave me alone
 * @lineptr: address of pointer to buffer
 * @n: The size of a preallocated pointer buffer
 *
 * Return: lots of things I don't care
 */
int _getline(myInfoObject *myInfo, char **lineptr, size_t *length)
{
	static char buf[MAX_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *lineptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = ReadBuffer(myInfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*lineptr = p;
	return (s);
}

/**
 * ReadBuffer  -  function reads data from a file descriptor into a buffer
 * @myInfo: idk
 * @buffer: The buffer
 * @i: idfk
 *
 *Return: the read size in bytes
*/
ssize_t ReadBuffer(myInfoObject *myInfo, char *buffer, size_t *i)
{
	ssize_t read_val = 0;

	if (*i == 0)
	{
		read_val = read(myInfo->read_file_descriptor, buffer, MAX_BUFFER_SIZE);
		if (read_val >= 0)
			*i = read_val;
	}
	return (read_val);
}
/**
 * GetInput - gets a line but without the new line
 * @myInfo: Hi again, it's me
 *
 * Return: The size of the read file
*/

ssize_t GetInput(myInfoObject *myInfo)
{
	static char *commandChainBuffer;
	static size_t currentPosition, nextPosition, bufferLength;
	ssize_t bytesRead = 0;
	char **currentCommand = &(myInfo->argument), *currentPositionPtr;

	_putchar(BUFFER_FLUSH_CONDITION);
	bytesRead = InputBuffer(myInfo, &commandChainBuffer, &bufferLength);
	if (bytesRead == -1)
		return (-1);

	if (bufferLength)
	{
		nextPosition = currentPosition;
		currentPositionPtr = commandChainBuffer + currentPosition;
		cSWC(myInfo, commandChainBuffer,
		&nextPosition, currentPosition, bufferLength);
		while (nextPosition < bufferLength &&
		!isThereChaining(myInfo, commandChainBuffer, &nextPosition))
			nextPosition++;

		currentPosition = nextPosition + 1;

		if (currentPosition >= bufferLength)
		{
			currentPosition = bufferLength = 0;
			myInfo->command_buffer_type = NORM_COMMAND;
		}

		*currentCommand = currentPositionPtr;
		return (_strlen(currentPositionPtr));
	}

	*currentCommand = commandChainBuffer;
	return (bytesRead);
}
/**
 * InputBuffer - chained buffer commands
 * @myInfo: struct parameter
 * @buffer: buffer's address
 * @length: address of the variable length
 *
 * Return: size of bytes read.
*/
ssize_t InputBuffer(myInfoObject *myInfo, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t newLength = 0;

	if (*length == 0)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigin);
#if USE_GETLINE
		bytesRead = getline(buffer, &newLength, stdin);
#else
		bytesRead = _getline(myInfo, buffer, &newLength);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			myInfo->linecount_flag = 1;
			removingComments(*buffer);
			BuildHistoryList(myInfo, *buffer, myInfo->history_count++);

			if (_strchr(*buffer, ';'))
			{
				*length = bytesRead;
				myInfo->command_buffer = buffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * GetHistoryFile - get history file
 * @myInfo: smth in a struct we made
 *
 * Return: history file
*/
char *GetHistoryFile(myInfoObject *myInfo)
{
	char *history_file = NULL;
	char *home_dir;
	size_t dir_len, file_len;

	home_dir = gettingEnviormentVariable(myInfo, "HOME=");

	if (home_dir)
	{
		dir_len = _strlen(home_dir);
		file_len = _strlen(HISTORY_FILE);
		history_file = malloc(sizeof(char) * (dir_len + file_len + 2));

		if (history_file)
		{
			_strcpy(history_file, home_dir);
			_strcat(history_file, "/");
			_strcat(history_file, HISTORY_FILE);
		}
	}
	return (history_file);
}
/**
 *WriteHistory - writes in a history file it created or it existed
 *@myInfo: اهلا بيك في مصر
 *
 *
 *Return: 1 on success
*/
int WriteHistory(myInfoObject *myInfo)
{
	int file_descriptor;
	char *filename;
	myList *current_node = NULL;

	filename = GetHistoryFile(myInfo);

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(filename);

	if (file_descriptor == -1)
	return (-1);

	for (current_node = myInfo->history; current_node;
	current_node = current_node->next)
	{
		_puts_fd(current_node->myString, file_descriptor);
		put_fd('\n', file_descriptor);
	}

	put_fd(BUFFER_FLUSH_CONDITION, file_descriptor);
	close(file_descriptor);

	return (1);
}
/**
 * ReadHistoryList - whatever
 * @myInfo: whatever
 * 
 * Return: SUCK YOUR MOM
 * 
*/
int ReadHistoryList(myInfoObject *myInfo)
{
	int i, last = 0, linecount = 0;
	ssize_t file_descriptor, read_length;
	struct stat file_stats;
	char *buffer = NULL, *filename;

	filename = GetHistoryFile(myInfo);

	file_descriptor = open(filename, O_RDONLY);

	if (!filename)
	return (0);

	if (fstat(file_descriptor, &file_stats) != 0)
	return (0);

	if (file_stats.st_size < 2)
	return (0);

	buffer = malloc(sizeof(char) * (file_stats.st_size + 1));
	if(buffer == NULL)
	return (0);

	read_length = read(file_descriptor, buffer, file_stats.st_size);

	buffer[file_stats.st_size] = '\0';
	close(file_descriptor);

	if (read_length <= 0)
	return (0);

	for (i = 0; i < file_stats.st_size; i++)
	{
		if (buffer[i] == '\n')
		{
			BuildHistoryList(myInfo, buffer + last, linecount);
			last = i + 1;
		}
	}
	if (last != 1)
	BuildHistoryList(myInfo, buffer + last, linecount);

	free (buffer);

	myInfo->history_count = linecount;

	while (myInfo->history_count-- >= 4096)
	delete_node_at_index(&(myInfo->history), 0);

	REM_History(myInfo);

	return (myInfo->history_count);
}
/**
 * BuildHistoryList - adds enrty to linked list
 * @myInfo: I DON"T GIVE A FART
 * @buffer: idc
 * @linecount: stll dc
 * 
 * Return: 0
*/
int BuildHistoryList(myInfoObject *myInfo, char *buffer, int linecount)
{
	myList *newnode = NULL;

	if (myInfo->history)
	newnode = myInfo->history;
	
	add_node_end(&newnode, buffer, linecount);

	if (!myInfo->history)
	myInfo->history = newnode;

	return (0);
}
/**
 * REM_History - Renumber the history linked list after changes
 * @myInfo: stfu
 * 
 * Return: new history count
*/
int REM_History(myInfoObject *myInfo)
{
	myList *current_node = myInfo->history;
	int new_histcount = 0;

	while (current_node)
	{
		current_node->theNum = new_histcount++;
		current_node = current_node->next;
	}

	myInfo->history_count = new_histcount;
	return (new_histcount);
}


/**
 * clearMyInfoVariable - A function to make the arguments in
 * my info variale NULL and zero
 * @myInfo: A pointer to my info varible
 *
 * Return: It returns nothing (void)
*/

void clearMyInfoVariable(myInfoObject *myInfo)
{
	(*myInfo).argument_count = 0;
	(*myInfo).path = NULL;
	(*myInfo).argument = NULL;
	(*myInfo).arguments = NULL;
}

/**
 * settingMyInfoVariable - A function to set the values of my info variable
 * @myInfo: A pointer to myInfo variable
 * @myArgv: An array of strings that contains the parameters
 * that are in command
 *
 * Return: Nothing (Void)
*/

void settingMyInfoVariable(myInfoObject *myInfo, char **myArgv)
{
	int i = 0;

	(*myInfo).filename = myArgv[0];
	if ((*myInfo).argument != NULL)
	{
		(*myInfo).arguments = strtow((*myInfo).argument, " \t");
		if ((*myInfo).arguments == NULL)
		{
			(*myInfo).arguments = malloc((sizeof(char *) * 2));
			if ((*myInfo).arguments != NULL)
			{
				(*myInfo).arguments[0] = _strdup((*myInfo).argument);
				(*myInfo).arguments[1] = NULL;
			}
		}
		for (i = 0; (*myInfo).argument != NULL && (*myInfo).arguments[i]; i++)
		;
		(*myInfo).argument_count = i;
	}
	replacingMyAliases(myInfo);
	replacingMyVariables(myInfo);
}

/**
 * freeMyInfo - A function to free the members of myInfo object
 * @myInfo: A pointer to myInfoObject variable
 * @allCondition: The condition to check if if we're going
 * to free some more members
 *
 * Return: Nothing (void)
*/

void freeMyInfo(myInfoObject *myInfo, int allCondition)
{
	freeAString((*myInfo).arguments);
	(*myInfo).arguments = NULL;
	(*myInfo).path = NULL;
	
	if (allCondition != 0)
	{
		if ((*myInfo).command_buffer != NULL)
			free((*myInfo).argument);
		if ((*myInfo).environment != NULL)
			free_list(&(*myInfo).environment);
		if ((*myInfo).history != NULL)
			free_list(&(*myInfo).history);
		if ((*myInfo).alias != NULL)
			free_list(&(*myInfo).alias);
		if ((*myInfo).environ != NULL)
			freeAString((*myInfo).environ);
		if ((*myInfo).read_file_descriptor > 2)
			close((*myInfo).read_file_descriptor);
		freeNulling((void **)(*myInfo).command_buffer);
		_putchar(BUFFER_FLUSH_CONDITION);
	}
}


/**
 * print_list - A function that prints the elements of a linked list
 * @h: A pointer to the head of the linked list
 *
 * Return: It returns the number of elements in the linked list
*/

size_t print_list(const myList *h)
{
    const myList *current = h;
    size_t counter = 0;

    while (current != NULL) {
        if (current->myString != NULL)
            _puts(current->myString);
        else
            _puts("(nil)");
        _putchar('\n');
        current = current->next;
        counter++;
    }

    return counter;
}

/**
 * addingNodeBeg - A function to add a node at the beginning of the
 * linked list
 * @myHead: A pointer to the head of the linked list
 * @myString: A pointer to the string that we want to put
 * in the linked list
 * @num: The number of the node in the history
 *
 * Return: NULL or a pointer to the newly created node
*/

myList *addingNodeBeg(myList **myHead, char *myString, int num)
{
	myList *newHead;

	if (myHead == NULL)
		return (NULL);
	newHead = malloc(sizeof(myList));
	if (newHead == NULL)
		return (NULL);
	_memset((void *)newHead, 0, sizeof(myList));
	(*newHead).theNum = num;
	if (myString != NULL)
	{
		(*newHead).myString = _strdup(myString);
		if ((*newHead).myString == NULL)
		{
			free(newHead);
			return (NULL);
		}
	}
	(*newHead).next = *myHead;
	*myHead = newHead;
	return (newHead);
}

/**
 * add_node_end - A function to add a node at the end
 * @head: A pointer to the pointer who points at the first node
 * @str: A string the should be inputed into the newly created node
 * @num: The number of the node in the history
 * Return: It returns a pointer to the newly created node
*/

myList *add_node_end(myList **head, char *str, int num)
{
	myList *newNode = (myList *)malloc(sizeof(myList));
	myList *current;

	if (newNode == NULL || head == NULL)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(newNode));
	(*newNode).theNum = num;
	if (str != NULL)
	{
		newNode->myString = _strdup(str);
        if (newNode->myString == NULL)
        {
            free(newNode);
            return (NULL);
        }
		newNode->next = NULL;
	}
	if (!*head)
	{
		*head = newNode;
		return (newNode);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = newNode;
	return (newNode);
}


/**
 * delete_nodeint_at_index - A function to delete a node at
 * a specific index
 * @head: A pointer to a pointer that points to the head
 * of the linked list
 * @index: The index of the node to be deleted
 *
 * Return: 1 or -1
*/

int delete_node_at_index(myList **head, unsigned int index)
{
	myList *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->myString);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->myString);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - A function to free the linked list
 * @head: A pointer to a pointer that
 * points to the head of the linked list
 *
 * Return: It returns nothing (void)
*/

void free_list(myList **head)
{
	myList *current = *head;
	myList *next;

	if (head == NULL || *head == NULL)
		return;
	while (current != NULL)
	{
		next = current->next;
		free(current->myString);
		free(current);
		current = next;
	}
	*head = NULL;
}


/**
 * linkedListLength - A function to return the lenghth of
 * the linked list
 * @myHead: A pointer to the head of the linked list
 *
 * Return: The length of the linked list
*/

size_t linkedListLength(myList *myHead)
{
	size_t theReturnedLength = 0;

	if (myHead == NULL)
		return (0);
	while (myHead != NULL)
	{
		theReturnedLength = theReturnedLength + 1;
		myHead = (*myHead).next;
	}
	return (theReturnedLength);
}

/**
 * printingTheList - A function to print the linked list
 * @myHead: A pointer to the head of the linked list
 *
 * Return: The size of the linked list
*/

size_t printingTheList(const myList *myHead)
{
	size_t AmrSize = 0;
	char *thePrintedNum;

	while (myHead != NULL)
	{
		thePrintedNum = convertor((*myHead).theNum, 10, 0);
		_puts(thePrintedNum);
		_puts(": ");
		if ((*myHead).myString == NULL)
			_puts("(nil)\n");
		else
		{
			_puts((*myHead).myString);
			_putchar('\n');
		}
		myHead = (*myHead).next;
		AmrSize = AmrSize + 1;
	}
	return (AmrSize);
}

/**
 * convertingNodeStringstoArray - A function to convert the strings
 * for a linked list to array of strings
 * @myHead: A pointer to the head of the linked list
 *
 * Return: A pointer to array of strings or NULL
*/

char **convertingNodeStringstoArray(myList *myHead)
{
	unsigned int length = linkedListLength(myHead);
	char **stringArrayPointer = malloc(sizeof(char *) * (length + 1));
	myList *currentNode = myHead;
	unsigned int i = 0, j = 0;
	char *tempStr;

	if (myHead == NULL || length == 0 || stringArrayPointer == NULL)
		return (NULL);
	while (currentNode != NULL)
	{
		tempStr = malloc(_strlen(currentNode->myString) + 1);
		if (tempStr == NULL)
		{
			for (; j < i; j++)
				free(stringArrayPointer[j]);
			free(stringArrayPointer);
			return (NULL);
		}
		_strcpy(tempStr, currentNode->myString);
		stringArrayPointer[i] = tempStr;
		currentNode = currentNode->next;
		i++;
	}
	stringArrayPointer[i] = NULL;

	return (stringArrayPointer);
}

/**
 * gettingTheIndex - A function to get the index of a node
 * @myHead: A pointer to the head of the linked list
 * @theRequiredNode: A pointer to the required node to find
 *
 * Return: It returns the index of node on success
 * and -1 on failure
*/

size_t gettingTheIndex(myList *myHead, myList *theRequiredNode)
{
	size_t theIndex = 0;

	if (myHead == NULL)
		return (0);

	while (myHead != NULL)
	{
		if (myHead == theRequiredNode)
			return (theIndex);
		theIndex = theIndex + 1;
		myHead = (*myHead).next;
	}
	return (1);
}

/**
 * isNodeStartsWith - A function to get the node which
 * starts with the required prefix
 * @myHead: A pointer to the head of the linked list
 * @theSearchPre: The required prefix or sub-string
 * to find
 * @afterChar: The char after the required prefix
 * and it's used in the condition
 *
 * if afterChar == -1 so that means it doesn't matter which char
 * is after the required prefix
 *
 * Return: A pointer to the required node or NULL
*/

myList *isNodeStartsWith(myList *myHead, char *theSearchPre, char afterChar)
{
	char *p = NULL;

	while (myHead)
	{
		p = startsWith(myHead->myString, theSearchPre);
		if (p && ((afterChar == -1) || (*p == afterChar)))
			return (myHead);
		myHead = myHead->next;
	}
	return (NULL);
}


/**
 * main - entry
 * @avrgv: The vector arguement
 * @argc: The count arguement
 *
 * Return: 0 on success, 1 on failure
*/

int main(int argc, char **argv)
{
	myInfoObject INFO [] = { Iintializing_INFO };
	int file_descriptor = 2;

	asm (
		"mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor)
	);

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		/*
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts(argv[0]);
				_puts(": 0; Can't open");
				_puts(argv[1]);
				_putchar('\n');
				_putchar(BUFFER_FLUSH_CONDITION);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		*/
		INFO->read_file_descriptor = file_descriptor;
	}

	makingtheLinkedList(INFO);
	/*ReadHistoryList(INFO);*/
	her_shell_hell(INFO, argv);

	return (EXIT_SUCCESS);
}



/**
 * findingMyBuiltinFunc - A function that gives us a pointer
 * to the required builtin functions that we have implmented
 * @myInfo: A pointer to myInfoObject that contains everything
 * about the shell currently
 *
 * Return: -1 on failure or other exiting condition
 * or success
*/

int findingMyBuiltinFunc(myInfoObject *myInfo)
{
	int i, myBuiltinRetValue = -1;

	myBuiltin myTableofBuilding[] = {
		{"exit", _exit_shell},
		{"env", printingEnviormentList},
		{"help", _help_},
		{"history", print_history},
		{"setenv", preparnigForSettingEnv},
		{"unsetenv", preparingForUnsettingEnv},
		{"cd", _cd_},
		{"alias", man_alias},
		{NULL, NULL}
	};

	for (i = 0; myTableofBuilding[i].nameofFunction != NULL; i++)
	{
		if (_strcmp(myTableofBuilding[i].nameofFunction,
		(*myInfo).arguments[0]) == 0)
		{
			(*myInfo).line_count = (*myInfo).line_count + 1;
			myBuiltinRetValue = myTableofBuilding[i].myCommandFun(myInfo);
			break;
		}
	}
	return (myBuiltinRetValue);
}

/**
 * forkingMyCmd - A function to fork the process when
 * we need to execute a commmand
 * @myInfo: A pointer to myInfoObject that contains everything
 * about the shell currently
 *
 * Return: Nothing (void)
*/

void forkingMyCmd(myInfoObject *myInfo)
{
	pid_t myChildPid = 0;
	int myReturnedStatus;

	myChildPid = fork();
	if (myChildPid == -1)
	{
		perror("Error: couldn't fork\n");
		return;
	}
	if (myChildPid == 0)
	{
		myReturnedStatus = execve((*myInfo).path,
		(*myInfo).arguments, gettingMyEnviron(myInfo));
		if (myReturnedStatus == -1)
		{
			freeMyInfo(myInfo, 1);
			/*
			if (errno == EACCES)
				exit(126);
			*/
			exit(1);
		}
	}
	else
	{
		wait(&(*myInfo).status);
		if (WIFEXITED((*myInfo).status))
		{
			(*myInfo).status = WEXITSTATUS((*myInfo).status);
			if ((*myInfo).status == 126)
				printingErrors(myInfo, "Permission denied\n");
		}
	}
}

/**
 * findingCommandLastTime - A function to find your command and
 * call the forking function to execute it
 * @myInfo: A pointer to myInfoObject that contains everything
 * about the shell currently
 *
 * Return: Nothing (void)
*/

void findingCommandLastTime(myInfoObject *myInfo)
{
	char *myEndPath = NULL;
	int i = 0, j = 0;

	(*myInfo).path = (*myInfo).arguments[0];
	if ((*myInfo).linecount_flag)
	{
		(*myInfo).line_count = ((*myInfo).line_count) + 1;
		(*myInfo).linecount_flag = 0;
	}
	for (; (*myInfo).argument[i] != '\0'; i++)
	{
		if (!is_del((*myInfo).argument[i], " \t\n"))
			j = j + 1;
	}
	if (j == 0)
		return;
	myEndPath = jOFP(myInfo,
	gettingEnviormentVariable(myInfo, "PATH="), (*myInfo).arguments[0]);
	if (myEndPath != NULL)
	{
		(*myInfo).path = myEndPath;
		forkingMyCmd(myInfo);
	}
	else
	{
		if ((isInteractive(myInfo) == true ||
		gettingEnviormentVariable(myInfo, "PATH=") != NULL ||
		(*myInfo).arguments[0][0] == '/') &&
		isExecutable(myInfo, (*myInfo).arguments[0]) == true)
			forkingMyCmd(myInfo);
		else if (*(*myInfo).argument != '\n')
		{
			(*myInfo).status = 127;
			printingErrors(myInfo, "not found\n");
		}
	}
}

/**
 * her_shell_hell - Most of the functions are here, The main Loop
 * @shellInfo: A pointer to myInfoObject that contains everythin
 * @arguments: The arguments vector passed from the main function
 *
 * Return: 0 on success, The error number on failure
*/

int her_shell_hell(myInfoObject *shellInfo, char *arguments[])
{
	int builtinResult = 0;
	ssize_t read_status = 0;

	while (read_status != -1 && builtinResult != -2)
	{
		clearMyInfoVariable(shellInfo);
		if (isInteractive(shellInfo) != 0)
			_puts("$ ");

		read_status = GetInput(shellInfo);
		if (read_status != -1)
		{
			settingMyInfoVariable(shellInfo, arguments);
			builtinResult = findingMyBuiltinFunc(shellInfo);
		if (builtinResult == -1)
			findingCommandLastTime(shellInfo);
		}
		else if (isInteractive(shellInfo))
			_putchar('\n');
		freeMyInfo(shellInfo, 0);
	}

	WriteHistory(shellInfo);
	freeMyInfo(shellInfo, 1);

	if (isInteractive(shellInfo) == 0 && shellInfo->status)
		exit(shellInfo->status);
	if (builtinResult == -2)
	{
		if (shellInfo->error_number == -1)
			exit(shellInfo->status);
		exit(shellInfo->error_number);
	}

	return (builtinResult);
}


/**
 * _memset - a function to set some memory locations to a specfic value
 * @s: Pointer to the array
 * @b: The value that we want to set to
 * @n: The number of bytes that we want to use
 * Description: Nothing
 * Return: pointer to the array
*/

char *_memset(char *s, char b, unsigned int n)
{
	char *p = s;

	while (n != 0)
	{
		*p = (unsigned char) b;
		p = p + 1;
		n = n - 1;
	}
	return (s);
}

/**
 * freeAString - A function to free a string
 * @myPointer: It's a function to free an array
 * of strings so this means we should have a pointer
 * to a pointer
 *
 * Return: nothing
*/

void freeAString(char **myPointer)
{
	char **current = myPointer;

    if (myPointer == NULL || *myPointer == NULL) {
        return;
    }
    while (*current != NULL) {
        free(*current);
        *current = NULL; /*Set the freed pointer to NULL to avoid dangling pointers*/
        current++;
    }

    free(myPointer);
}

/**
 * freeNulling - A function that frees that content of a pointer
 * and sets the pointer to null
 * @myPointer: A pointer to a pointer to be freed
 *
 * Return: true or false
*/

bool freeNulling(void **myPointer) /*bFree*/
{
	if (myPointer != NULL && *myPointer != NULL)
	{
		free(*myPointer);
		myPointer = NULL;
		return (true);
	}
	return (false);
}


/**
 * _realloc - A function that is equal to realloc
 * @ptr: Pointer to a previously allocated memory
 * @old_size: It's the size of the old allocated memory
 * @new_size: It's the size of the new allocated memory
 *
 * Return: It returns a pointer to the new allocated
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *ptrnew;

	if (old_size == new_size)
		return (ptr);

	if (ptr == NULL)
	{
		ptrnew = malloc(new_size);
		if (ptrnew == NULL)
			return (NULL);

		return (ptrnew);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	ptrnew = malloc(new_size);
	if (ptrnew == NULL)
		return (NULL);
	if (old_size > new_size)
	{
		_memcpy(ptrnew, ptr, new_size);
	}
	else
	{
		_memcpy(ptrnew, ptr, old_size);
	}
	free(ptr);
	return (ptrnew);
}

/**
 * _memcpy - A function to copies some bytes from place to another
 * @dest: Pointer to dest chars
 * @src: Pointer to src chars
 * @n: Number of bytes to be copied
 * Description: Nothing
 * Return: Pointer to dest array
*/

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;
	char *cdest = (char *) dest;
	char *csrc = (char *) src;

	for (i = 0; i < n; i++)
		cdest[i] = csrc[i];

	return (dest);
}

/**
 * isInteractive - A function to check if we're at the interactive mode
 * or not
 * @myInfo: An object of type myInfoObject
 *
 * Return: True or false
*/

bool isInteractive(myInfoObject *myInfo)
{
	if (isatty(0) && (*myInfo).read_file_descriptor <= 2) /*STDIN_FILENO*/
		return (true);
	else
		return (false);
}

/**
 * _isalpha - A function if a char is alpha or not
 * @myChar: The char to be checked
 *
 * Return: True or False
*/

bool _isalpha(int myChar)
{
	if ((myChar >= 'a' && myChar <= 'z') || (myChar >= 'A' && myChar <= 'Z'))
		return (true);
	else
		return (false);
}


/**
 * _atoi - A function that converts a string to integer
 * @s: The required string to be converted
 * Description:This function loops through each digits and
 * check some conditions to get the required integer
 * Return: It returns the integer in the string
*/

int _atoi(char *s)
{
	int i, strLength, oddSigns, flag, lastNumber, digit;

	i = 0;
	strLength = 0;
	oddSigns = 0;
	flag = 0;
	lastNumber = 0;
	digit = 0;

	while (s[strLength] != '\0')
		strLength++;

	while (i < strLength && flag == 0)
	{
		if (s[i] == '-')
			oddSigns = oddSigns + 1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (oddSigns % 2 != 0)
				digit = -1 * digit;
			lastNumber = lastNumber * 10 + digit;

			flag = 1;

			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			flag = 0;
		}
		i++;
	}

	if (flag == 0)
		return (0);
	return (lastNumber);
}

/**
 * is_del - checks if a character is a delimiter
 * @c: the character to check
 * @del: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_del(char c, char *del)
{
	while (*del != '\0')
	{
		if (c == *del)
			return (1);
		del++;
	}
	return (0);
}


/**
 * printingErrors - A function to print error on the terimanl
 * (stderr)
 * @myInfo: A pointer to myInfo variable
 * @myError: A pointer to string that cointains
 * the error string
 *
 * Return: Nothing (void)
*/

void printingErrors(myInfoObject *myInfo, char *myError)
{
	_puts_fd((*myInfo).filename, 2); /*STDERR_FILENO*/
	_puts_fd(": ", 2);
	printingDecimal((*myInfo).line_count, 2);
	_puts_fd(": ", 2);
	_puts_fd((*myInfo).arguments[0], 2);
	_puts_fd(": ", 2);
	_puts_fd(myError, 2);
}

/**
 * convertor - converter function, a clone of itoa
 * @num: number
 * @myBase: base
 * @myFlags: argument flags
 *
 * Return: string
 */

char *convertor(long int num, int myBase, int myFlags)
{
	char numbersArray[40];
	static char myBuffer[50];
	char theSign = 0;
	char *ptr;
	unsigned long conditionNum = num;

	if (!(myFlags & IS_UNSIGNED) && num < 0)
	{
		conditionNum = -1 * num;
		theSign = '-';
	}
	if (myFlags & IS_LOWERCASE)
		_strcpy(numbersArray, "0123456789abcdef");
	else
		_strcpy(numbersArray, "0123456789ABCDEF");

	ptr = &myBuffer[49];
	*ptr = '\0';
	do {
		ptr = ptr - 1;
		*ptr = numbersArray[conditionNum % myBase];
		conditionNum = conditionNum / myBase;
	} while (conditionNum);

	if (theSign != 0)
	{
		ptr = ptr - 1;
		*ptr = theSign;
	}
	return (ptr);
}

/**
 * removingComments - A function to remove comments from a buffer
 * passed to it
 * @myBuffer: A Pointer to string which is the buffer
 *
 * echo "My name is Amr" # (example)
 * #echo "My name is Amr"
 * Return: Nothing (void)
*/

void removingComments(char *myBuffer)
{
	int theLooperF;

	for (theLooperF = 0; *(myBuffer + theLooperF) != '\0'; theLooperF++)
	{
		if (*(myBuffer + theLooperF)  == '#'
		&& (theLooperF == 0 || myBuffer[theLooperF - 1] == ' '))
		{
			*(myBuffer + theLooperF) = '\0';
			break;
		}
	}
}

/**
 * errorToInteger - A function to convert an error to integer
 * @myError: A pointer to a string that represnts
 * the error
 *
 * Return: 0 on Success and -1 on Failure
*/

int errorToInteger(char *myError)
{
	int AmrLooper = 0;
	unsigned long int finalResult = 0;

	if (*myError == '+')
		myError = myError + 1;
	for (; myError[AmrLooper]; AmrLooper++)
	{
		if (myError[AmrLooper] >= '0' && myError[AmrLooper] <= '9')
		{
			finalResult = finalResult * 10 + (myError[AmrLooper] - '0');
			if (finalResult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (finalResult);
}

/**
 * printingDecimal - A function to print the decimal numbers to the
 * standard output or standard error
 * @myInput: The number to be printed
 * @fileD: The file desciptor that deterimines that
 * we're going to print on the standard output
 * or standard error
 *
 * Return: The number of chars that were printed
*/

int printingDecimal(int myInput, int fileD)
{
	int (*myPrintFunction)(char) = _putchar;
	int printedChars = 0;
	unsigned int myAbsolute, myCurrent;
	unsigned int myDivisor = 1000000000;

	if (fileD == 2) /*STDERR_FILENO*/
		myPrintFunction = _errorputchar;
	if (myInput < 0)
	{
		myAbsolute = -myInput;
		myPrintFunction('-');
		printedChars = printedChars + 1;
	}
	else
		myAbsolute = myInput;
	myCurrent = myAbsolute;
	while (myDivisor >= 1)
	{
		if (myCurrent / myDivisor != 0)
		{
			myPrintFunction(myCurrent / myDivisor + '0');
			printedChars = printedChars + 1;
		}
		myCurrent = myCurrent % myDivisor;
		myDivisor = myDivisor / 10;
	}
	myPrintFunction(myCurrent + '0');
	printedChars = printedChars + 1;

	return (printedChars);
}


/**
 * put_fd - writes c to the file_descriptor given
 * @c: The charcter to be printe
 * @file_descriptor: the file to write to
 *
 * Return: 1 on success, -1 on failure
*/
int put_fd(char c, int file_descriptor)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (c == BUFFER_FLUSH_CONDITION || MAX_BUFFER_SIZE <= i)
	{
		write(file_descriptor, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH_CONDITION)
	{
		buffer[i++] = c;
	}
	return (1);
}

/**
 *  _puts_fd - like _puts it uses put_fd to write to the file
 * @string: The string
 * @file_descriptor: The file to write to
 *
 * Return: The number of characters
*/

int _puts_fd(char *string, int file_descriptor)
{
	int i = 0;

	if (string == NULL)
	return (0);

	while (*string != '\0')
	{
		i = i + put_fd(*string, file_descriptor);
		string = string + 1;
	}
	return (i);
}

/**
 * _errorputchar - A function to print errors
 * to the standard error
 * @myChar: The char to be printed to the standard error
 *
 * Return: The number of the chars that was printed
*/

int _errorputchar(char myChar)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (myChar == BUFFER_FLUSH_CONDITION || MAX_BUFFER_SIZE <= i)
	{
		write(2, buffer, i); /*STDERR_FILENO*/
		i = 0;
	}
	if (myChar != BUFFER_FLUSH_CONDITION)
	{
		buffer[i++] = myChar;
	}
	return (1);
}

/**
 * _errorputschar - A function to put a string on the
 * standard error
 * @myString: A pointer to the string that will be
 * printed to the standard error
 *
 * Return: Nothing (void)
*/

void _errorputschar(char *myString)
{
	if (!myString)
	return;

	while (*myString)
		_errorputchar(*myString++);
}


/**
 * _strlen - counts the length of a string
 * @str: The string
 * Return: The length of success
*/
int _strlen(char *str)
{
	int len;

	if (!str)
	return (0);

	while (*str)
	{
		len++;
		str = str + 1;
	}
	return (len);
}
/**
 * _strcmp - A function to compare two strings
 * @X: First string to be compared
 * @Y: Second string to be compared
 * Description: This function loops through each char in
 * the X and Y and when it finds any different char
 * it breaks out of the loop and return the value of their ASCII values
 * substraction
 * Return: 0 if they are equal, a positive number if X is bigger
 * than Y, a negative number if X is smaller than Y
*/

int _strcmp(char *X, char *Y)
{
	while (*X)
	{
		if (*X != *Y)
			break;

		X = X + 1;
		Y = Y + 1;
	}

	return (*(const unsigned char *)X - *(const unsigned char *)Y);
}
/**
 * _strcat - A function that concatenates two strings together
 * @dest: The first string
 * @src: The second string that has to concatenated with
 * the first one
 * Return: It returns a pointer to the beginning of the
 * concatenated string
*/

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strcpy - copies a string
 * @str1: The fist string
 * @str2: The second string
 * Return: The copy
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
 * _strncpy - copies a string
 * @str1: The fist string
 * @str2: The second string
 * @n: The number of characters to be copied
 * Return: The copy
*/
char *_strncpy(char *str1, char *str2, int n)
{
	int i;

	for (i = 0; i < n - 1 && *str2 != '\0'; i++)
	str1[i] = str2[i];

		while (i < n)
		{
			str1[i] = '\0';
			i++;
		}

	return (str1);
}


/**
 * _strdup - A function that creates a new array using DMP
 * and it copies the contents of a given string to the new
 * array that is allocated dynamically
 * @str: Pointer to the given string
 *
 * Return: A pointer to the new allocated array or NULL
*/

char *_strdup(char *str)
{
	int i;

	if (str != NULL)
	{
		char *newArray = (char *)malloc(_strlen(str) * sizeof(char) + 1);

		if (newArray == NULL)
		{
			return (NULL);
		}
		else
		{
			for (i = 0; i < _strlen(str); i++)
				_strcpy((newArray + i), (str + i));
			return (newArray);
		}
	}
	else
	{
		return (NULL);
	}
}

/**
 * startsWith - A function to check if a string starts with
 * a specfic sub-string
 * @myString: The big string that we search in
 * @theSString: The sub-string
 *
 * Return: It returns a char pointer to current poistion
 * of the big string after searching or it may returns null
*/

char *startsWith(const char *myString, const char *theSString)
{
	while (*theSString != '\0')
	{
		if (*myString != *theSString)
			return (NULL);
		myString = myString + 1;
		theSString = theSString + 1;
	}
	return ((char *)myString);
}

/**
 * _strchr - A function that returns the poisition of a specfic char
 * @myString: A pointer to the string that we search in
 * @myChar: The char that we're searching for
 *
 * Return: NULL or the poistion
*/

char *_strchr(char *myString, char myChar)
{
	if (myString == NULL)
		return (NULL);
	while (*myString != '\0' && *myString != myChar)
		myString = myString + 1;
	if (*myString == myChar)
		return (myString);
	else
		return (NULL);
}


/**
 *_strncat - concatenates two strings
 *@dest:idk
 *@src: idk
 *@n: number of bytes
 *Return: dest
*/
char *_strncat(char *dest, char *src, int n)
{
		int i, j, L, L2, L3;

		if (dest == NULL || src == NULL)
		return NULL;

		L = strlen(dest);
		L2 = L + n;
		L3 = strlen(src);

		if (L2 >= MAX_BUFFER_SIZE)
		return NULL;

		for (i = L, j = 0; i < L2 && j < L3; i++, j++)
		{
			dest[i] = src[j];
		}
		return (dest);
}

/**
 * _puts - prints a string
 * @s: the string to be printed
 * Description: It loops on -putchar to print a string
 * Return: nothing
*/

void _puts(char *s)
{
	if (!s)
	return;

	while (*s)
		_putchar(*s++);
}


/**
 * _putchar - it prints a single character
 * @c: the character to be printed
 * Return: 1 on success
*/

int _putchar(char c)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (c == BUFFER_FLUSH_CONDITION || MAX_BUFFER_SIZE <= i)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH_CONDITION)
	{
		buffer[i++] = c;
	}
	return (1);
}

/**
 * strtow2 - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
*/

char **strtow2(char *str, char *del)
{
    int i, j, k, n, m, count = 0, len = 0, l;
    char **words = NULL;

    if (str == NULL || del == NULL)
        return (NULL);
    n = _strlen(str);
    m = _strlen(del);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (str[i] == del[j])
                break;
        }
        if (j == m && (i == 0 || (j != m - 1 && str[i - 1] == del[m - 1])))
            count++;
    }
    words = (char **)malloc((count + 1) * sizeof(char *));
    if (words == NULL)
        return (NULL);
    for (i = 0, j = 0; i < n && j < count; i++)
    {
        for (k = 0; k < m; k++)
        {
            if (str[i] == del[k])
                break;
        }
        if (k == m && (i == 0 || (k != m - 1 && str[i - 1] == del[m - 1])))
        {
            len = i - j;
            words[j] = (char *)malloc((len + 1) * sizeof(char));
            if (words[j] == NULL)
            {
                for (l = 0; l < j; l++)
                    free(words[l]);
                free(words);
                return (NULL);
            }
            _strncpy(words[j], str + j, len);
            words[j][len] = '\0';
            j++;
        }
    }
    words[count] = NULL;
    return (words);
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *del)
{
	char **words = NULL;
	int num_words = 0, str_len, del_len, word_start, i = 0, word_len, j;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (del == NULL)
		del = " ";

	str_len = strlen(str);
	del_len = strlen(del);

	while (i < str_len)
	{
		while (i < str_len && is_del(str[i], del))
			i++;

		if (i == str_len)
			break;

	word_start = i;

	while (i < str_len && !is_del(str[i], del))
		i++;

	word_len = i - word_start;
	num_words++;

	char **temp = realloc(words, (num_words + 1) * sizeof(char *));
	if (temp == NULL)
	{
		for (j = 0; j < num_words - 1; j++)
			free(words[j]);
		free(words);
		return (NULL);
	}
	words = temp;

	words[num_words - 1] = malloc((word_len + 1) * sizeof(int));
	if (words[num_words - 1] == NULL)
	{
		for (j = 0; j < num_words - 1; j++)
		free(words[j]);
			free(words);
	return (NULL);
	}

	strncpy(words[num_words - 1], str + word_start, word_len);
	words[num_words - 1][word_len] = '\0';
	}

	if (num_words == 0)
	{
		free(words);
		return (NULL);
	}

	words[num_words] = NULL;
	return (words);
}

/**
 * 1 fixing startsWith
 * 
*/