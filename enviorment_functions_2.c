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
             	(*myInfo).environ = turningListsToStrings((*myInfo).environment);
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
                        (*myInfo).environment_changed = deleteNodeIndex(&(*myInfo).environment, i);
                        i = 0;
                        myHead = (*myInfo).environment;
                        continue;
                }
                myHead = (*myHead).next;
                i++;
	}
	return ((*myInfo).environment_changed);
}
