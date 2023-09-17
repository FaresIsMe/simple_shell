#include "shell.h"

/**
 * _memset - a function to set some memory locations to a specfic value
 * @s: Pointer to the array
 * @b: The value that we want to set to
 * @n: The number of bytes that we want to use
 * Description: Nothing
 * Return: pointer to the array
*/

char *_memset(char *s, char b, unsigned int n)
{
	char *p = s;

	while (n != 0)
	{
		*p = (unsigned char) b;
		p = p + 1;
		n = n - 1;
	}
	return (s);
}

/**
 * freeAString - A function to free a string
 * @myPointer: It's a function to free an array
 * of strings so this means we should have a pointer
 * to a pointer
 *
 * Return: nothing
*/

void freeAString(char **myPointer) /*fFree*/
{
	char **myTemp = myPointer;

	if (*myPointer == NULL || myPointer == NULL)
		return;
	while (*myPointer != NULL)
	{
		free(*myPointer);
		myPointer = myPointer + 1;
	}
	free(myTemp);
}

/**
 * freeNulling - A function that frees that content of a pointer
 * and sets the pointer to null
 * @myPointer: A pointer to a pointer to be freed
 *
 * Return: true or false
*/

bool freeNulling(char **myPointer) /*bFree*/
{
	if (myPointer != NULL && *myPointer != NULL)
	{
		free(*myPointer);
		myPointer = NULL;
		return (true);
	}
	return (false);
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
		_memcpy(ptrnew, ptr, new_size);
	}
	else
	{
		_memcpy(ptrnew, ptr, old_size);
	}
	free(ptr);
	return (ptrnew);
}

/**
 * _memcpy - A function to copies some bytes from place to another
 * @dest: Pointer to dest chars
 * @src: Pointer to src chars
 * @n: Number of bytes to be copied
 * Description: Nothing
 * Return: Pointer to dest array
*/

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;
	char *cdest = (char *) dest;
	char *csrc = (char *) src;

	for (i = 0; i < n; i++)
		cdest[i] = csrc[i];

	return (dest);
}
