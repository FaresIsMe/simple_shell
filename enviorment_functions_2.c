#include "shell.h"

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
			(*myInfo).environment_changed = delete_node_at_index(
			&(*myInfo).environment, i);
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
	char *buf = NULL;
	myList *node;
	char *p;

	if (!myVar|| !myValue)
		return (0);

	buf = malloc(_strlen(myVar) + _strlen(myValue) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, myVar);
	_strcat(buf, "=");
	_strcat(buf, myValue);
	node = myInfo->environment;
	while (node)
	{
		p = startsWith(node->myString, myVar);
		if (p && *p == '=')
		{
			free(node->myString);
			node->myString = buf;
			myInfo->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(myInfo->environment), buf, 0);
	free(buf);
	myInfo->environment_changed = 1;
	return (0);
}
