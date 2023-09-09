#include "shell.h"

/**
 *_strncat - concatenates two strings
 *@dest:idk
 *@src: idk
 *@n: number of bytes
 *Return: dest
*/
char *_strncat(char *dest, char *src, int n)
{
		int i, j, L, L2, L3;

		L = strlen(dest);
		L2 = L + n;
		L3 = strlen(src);
		for (i = L, j = 0; i < L2 && j < L3; i++, j++)
		{
			dest[i] = src[j];
		}
		return (dest);
}

/**
 * _puts - prints a string
 * @s: the string to be printed
 * Description: It loops on -putchar to print a string
 * Return: nothing
*/

void _puts(char *s)
{
	if (!s)
	return;

	while (*s)
		_putchar(*s++);
}


/**
 * _putchar - it prints a single character
 * @c: the character to be printed
 * Return: 1 on success
*/

int _putchar(char c)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (c == BUFFER_FLUSH_CONDITION || MAX_BUFFER_SIZE <= i)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH_CONDITION)
	{
		buffer[i++] = c;
	}
	return (1);
}


/**
 * _realloc - A function that is equal to realloc
 * @ptr: Pointer to a previously allocated memory
 * @old_size: It's the size of the old allocated memory
 * @new_size: It's the size of the new allocated memory
 *
 * Return: It returns a pointer to the new allocated
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *ptrnew;

	if (old_size == new_size)
		return (ptr);

	if (ptr == NULL)
	{
		ptrnew = malloc(new_size);
		if (ptrnew == NULL)
			return (NULL);

		return (ptrnew);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	ptrnew = malloc(new_size);
	if (ptrnew == NULL)
		return (NULL);
	if (old_size > new_size)
	{
		memcpy(ptrnew, ptr, new_size);
	}
	else
	{
		memcpy(ptrnew, ptr, old_size);
	}
	free(ptr);
	return (ptrnew);
}
