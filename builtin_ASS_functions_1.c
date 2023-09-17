#include "shell.h"

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
	int AMR_dir;

	current_dir = getcwd(FARES, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!myInfo->arguments[1])
	{
		target_dir = gettingEnviormentVariable(myInfo, "HOME=");
		if (!target_dir)
		AMR_dir = chdir(target_dir ? target_dir : "/");
		else
		AMR_dir = chdir(target_dir);
	}
	else if (_strcmp(myInfo->arguments[1], "-") == 0)
	{
		target_dir = gettingEnviormentVariable(myInfo, "OLDPWD=");
		if (!target_dir)
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(target_dir);
		_putchar('\n');
		AMR_dir = chdir(target_dir);
	}
	else
	{

		AMR_dir = chdir(myInfo->arguments[1]);
	}
	if (AMR_dir == -1)
	{
		printingErrors(myInfo, "can't cd to ");
		_puts(target_dir);
		_putchar('\n');
	}
	else
	{
		settingEnvVar(myInfo, "OLDPWD", gettingEnviormentVariable(myInfo, "PWD="));
		settingEnvVar(myInfo, "PWD", getcwd(FARES, 1024));
	}
	return (0);
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