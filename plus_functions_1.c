#include "shell.h"
/**
 * isInteractive - A function to check if we're at the interactive mode
 * or not
 * @myInfo: An object of type myInfoObject
 *
 * Return: True or false
*/

bool isInteractive(myInfoObject *myInfo)
{
	if (isatty(STDIN_FILENO) && (*myInfo).read_file_descriptor <= 2)
		return (true);
	else
		return (false);
}

/**
 * _isalpha - A function if a char is alpha or not
 * @myChar: The char to be checked
 *
 * Return: True or False
*/

bool _isalpha(int myChar)
{
	if ((myChar >= 'a' && myChar <= 'z') || (myChar >= 'A' && myChar <= 'Z'))
		return (true);
	else
		return (false);
}


/**
 * _atoi - A function that converts a string to integer
 * @s: The required string to be converted
 * Description:This function loops through each digits and
 * check some conditions to get the required integer
 * Return: It returns the integer in the string
*/

int _atoi(char *s)
{
	int i, strLength, oddSigns, flag, lastNumber, digit;

	i = 0;
	strLength = 0;
	oddSigns = 0;
	flag = 0;
	lastNumber = 0;
	digit = 0;

	while (s[strLength] != '\0')
		strLength++;

	while (i < strLength && flag == 0)
	{
		if (s[i] == '-')
			oddSigns = oddSigns + 1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (oddSigns % 2 != 0)
				digit = -1 * digit;
			lastNumber = lastNumber * 10 + digit;

			flag = 1;

			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			flag = 0;
		}
		i++;
	}

	if (flag == 0)
		return (0);
	return (lastNumber);
}

/**
 * is_del - checks if a character is a delimiter
 * @c: the character to check
 * @del: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_del(char c, char *del)
{
	while (*del != '\0')
	{
		if (c == *del)
			return (1);
		del++;
	}
	return (0);
}
