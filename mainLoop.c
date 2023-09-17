#include "shell.h"


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
	pid_t myChildPid;
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
		(*myInfo).argument, gettingMyEnviron(myInfo));
		if (myReturnedStatus == -1)
		{
			freeMyInfo(myInfo);
			if (errno == EACCES)
				exit(126);
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
				printingErros(myInfo, "Permission denied\n");
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
	for (; (*myInfo).argument[i] != NULL; i++)
	{
		if (is_del((*myInfo).argument, " \t\n"))
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
			printingErros(myInfo, "not found\n");
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

	if (isInteractive(shellInfo) == NULL && shellInfo->status)
		exit(shellInfo->status);

	if (builtinResult == -2)
	{
		if (shellInfo->error_number == -1)
			exit(shellInfo->status);
	}

	while (read_status != -1 && builtinResult != -2)
	{
		clearMyInfoVariable(shellInfo);
		if (isInteractive(shellInfo) != NULL)
			_puts("$ ");

		read_status = GetInput(shellInfo);
		if (read_status == -1)
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

	return (builtinResult);
}
