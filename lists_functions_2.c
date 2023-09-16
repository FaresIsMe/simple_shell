#include "shell.h"

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
 * convertingNodeStringtoArray - A function to convert the strings
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

    if (myHead == NULL || length == 0 || stringArrayPointer == NULL )
		return (NULL);
    while (currentNode != NULL)
    {
        tempStr = malloc(_strlen(currentNode->myString) + 1);
        if (tempStr == NULL)
        {
            for (unsigned int j = 0; j < i; j++)
                free(stringArrayPointer[j]);
            free(stringArrayPointer);
            return NULL;
        }
        _strcpy(tempStr, currentNode->myString);
        stringArrayPointer[i] = tempStr;
        currentNode = currentNode->next;
        i++;
    }
    stringArrayPointer[i] = NULL;

    return stringArrayPointer;
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
	char *myPointer = NULL;

	while (myHead != NULL)
	{
		myPointer = startsWith((*myHead).myString, theSearchPre);
		if (myPointer != NULL &&
		(afterChar == -1 || *theSearchPre == afterChar))
		{
			return (myHead);
		}
		myHead = (*myHead).next;
	}
	return (NULL);
}