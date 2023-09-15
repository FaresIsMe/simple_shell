#include "shell.h"


/**
 * isExecutable - A function to check if the file is executable or not
 * @myP: A Pointer to myInfoObject variable
 * and it's not used in this function
 * @FaresPath: The path to the file that we want to check
 *
 * Return: 0 on failling and 1 on success
*/

bool isExecutable(__attribute__((unused)) myInfoObject *myP, char *FaresPath)
{
	struct stat myStatVar;

	if (FaresPath == NULL)
		return (false);
	if (stat(FaresPath, &myStatVar) != 0)
		return (false);
	return (S_ISREG & myStatVar.st_mode ? true : false);
}

/**
 * duplicatingMyChars - A function to get sub-strings of
 * a path string
 * @myPathStr: A pointer to a string
 * that contains the path of a file
 * @myStart: The beginning of the path string
 * that we want to start exctracting from
 * @myEnd: The end of the path string
 * that we want to end the exctracting
 *
 * Return: A pointer to the buffer that contains
 * the sub-string
*/

char *duplicatingMyChars(char *myPathStr, int myStart, int myEnd)
{
	static char myBuffer[MAX_BUFFER_SIZE];
	int i = 0, bufferPos;

	for (bufferPos = 0, i < myStart; i < myEnd; i++)
	{
		if (myPathStr[i] != ':')
		{
			myBuffer[bufferPos] = myPathStr[i];
			bufferPos = bufferPos + 1;
		}
	}
	myBuffer[bufferPos] = '\0';
	return (myBuffer);
}

