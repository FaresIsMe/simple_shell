#include "shell.h"

/**
 * _strlen - counts the length of a string
 * @str: The string
 * Return: The length of success
*/
int _strlen(char *str)
{
	int i = 0;

	if (!str)
	return (0);

	while (*str++)
		i++;
	return (i);
}
/**
 * _strcmp - A function to compare two strings
 * @X: First string to be compared
 * @Y: Second string to be compared
 * Description: This function loops through each char in
 * the X and Y and when it finds any different char
 * it breaks out of the loop and return the value of their ASCII values
 * substraction
 * Return: 0 if they are equal, a positive number if X is bigger
 * than Y, a negative number if X is smaller than Y
*/

int _strcmp(char *X, char *Y)
{
	while (*X)
	{
		if (*X != *Y)
			break;

		X = X + 1;
		Y = Y + 1;
	}

	return (*(const unsigned char *)X - *(const unsigned char *)Y);
}
/**
 * _strcat - A function that concatenates two strings together
 * @dest: The first string
 * @src: The second string that has to concatenated with
 * the first one
 * Return: It returns a pointer to the beginning of the
 * concatenated string
*/

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strcpy - copies a string
 * @dest: The fist string
 * @src: The second string
 * Return: The copy
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
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
