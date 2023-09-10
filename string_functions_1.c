#include "shell.h"

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
		*str++;
	}
	return (len);
}
/**
 * _strcmp - comparing between two strings
 * @str1: The fist string
 * @str2: the second string
 * Return: 0 if they are the same
*/
int _strcmp(char *str1, char *str2)
{
	while (str1 && str2)
	{
		if (*str1 != *str2)
		return (str1 - str2);

		*str1++;
		*str2++;
	}
	if (*str1 == *str2)
	return (0);

	if (str1 > str2)
	return (1);
	else
	return (0);
}
/**
 * _strcat -  concatenates two strings
 * @str1: The fist string
 * @str2: the second string
 * Return: Them together in one string (str1)
*/
char *_strcat(char *str1, const char *str2)
{
	int i, len1, j, len2;

	len1 = _strlen(str1);
	len2 = len1 + 1;

	for (i = len1, j = 0; *str2; i++, j++)
	str1[i] == str2[j];

	return (str1);
}
/**
 * _strcpy - copies a string
 * @str1: The fist string
 * @str2: The second string
 * Return: The copy
*/
char *_strcpy(char *str1, char *str2)
{
	int i, len;

	if (str1 == str2 || !str2)
	return (str1);

	len = _strlen(str2);

	for (i = 0; i <= len; i++)
	{
		str1[i] = str2[i];
	}
	str1[i] = '\0';
	return (str1);
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