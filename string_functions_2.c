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
	unsigned int i;

	if (str != NULL)
	{
		char *newArray = (char *)malloc(_strlen(str) * sizeof(char) + 1);

		if (newArray == NULL)
		{
			return (NULL);
		}
		else
		{
			for (i = 0; i < _strlen(str); i++)
				_strcpy((newArray + i), (str + i));
			return (newArray);
		}
	}
	else
	{
		return (NULL);
	}
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
	while (*myString != '\0')
	{
		if (*myString != *theSString)
			return (NULL);
		myString = myString + 1;
		mySString = mySString + 1;
	}
	return ((char *)myString);
}


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
 * _strchr - A function that returns the poisition of a specfic char
 * @myString: A pointer to the string that we search in
 * @myChar: The char that we're searching for
 *
 * Return: NULL or the poistion
*/

char *_strchr(const char *myString, char myChar)
{
	if (myString == NULL)
		return (NULL);
	while(*myString != '\0' && *myString != myChar)
		myString = myString + 1;
	if (*myString == myChar)
		return (myString);
	else
		return (NULL);	
}

