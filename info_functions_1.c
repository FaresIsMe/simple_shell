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
	replacingAlliasing(myInfo);
	replacingVariables(myInfo);
}

