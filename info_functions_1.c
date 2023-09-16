#include "shell.h"

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
			(*myInfo).arguments = (sizeof(char *) * 2);
			if ((*myInfo).arguments != NULL)
			{
				(*myInfo).arguments[0] = _strdub((*myInfo).argument);
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
	(*myInfo).path = NULL;
	freeAString((*myInfo).arguments);
	(*myInfo).arguments = NULL;

	if (allCondition != 0)
	{
		if ((*myInfo).command_buffer != NULL)
			free((*myInfo).argument);
		if ((*myInfo).environment != NULL)
			free(&(*myInfo).environment);
		if ((*myInfo).history != NULL)
			free(&(*myInfo).history);
		if ((*myInfo).alias != NULL)
			free(&(*myInfo).alias);
		if ((*myInfo).environ != NULL)
			free((*myInfo).environ);
		if ((*myInfo).read_file_descriptor > 2)
			close((*myInfo).read_file_descriptor);
		freeNulling((void **)(*myInfo).command_buffer);
		_putchar(BUFFER_FLUSH_CONDITION);
	}
}
