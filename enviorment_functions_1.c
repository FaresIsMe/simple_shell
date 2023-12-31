#include "shell.h"

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
		_puts_fd("Not correct number of arguments I think \n", STDERR_FILENO);
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
		_puts_fd("Not correct number of arguments\n", STDERR_FILENO);
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
