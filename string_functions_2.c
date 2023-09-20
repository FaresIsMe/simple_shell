#include "shell.h"

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
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
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

