#include "shell.h"


/**
 * isExecutable - A function to check if the file is executable or not
 * @myP: A Pointer to myInfoObject variable
 * and it's not used in this function
 * @FaresPath: The path to the file that we want to check
 *
 * Return: 0 on failling and 1 on success
*/

bool isExecutable(__attribute__((unused)) myInfoObject * myP, char *FaresPath)
{
	struct stat myStatVar;

	if (FaresPath == NULL || stat(FaresPath, &myStatVar))
		return (false);
	if (myStatVar.st_mode & S_IFREG) /*myStatVar.st_mode & S_IFREG*/
		return (true);
	return (false);
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

	for (bufferPos = 0, i = myStart; i < myEnd; i++)
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


/**
 * jOFP - A function to find the path of the required command
 * @myInfo: A pointer to myInfoObject variable
 * @pathEnvVar: The PATH enviorment variable
 * @myCommand: The required command to be execuated
 *
 * Return: A pointer to the full path or NULL
*/

char *jOFP(myInfoObject *myInfo, char *pathEnvVar, char *myCommand)
{	/*journey of finding path*/
	int i = 0, myCurrentPos = 0;
	char *myEndPath;

	if (pathEnvVar == NULL)
		return (NULL);
	if ((_strlen(myCommand) > 2) && startsWith(myCommand, "./"))
	{
		if (isExecutable(myInfo, myCommand))
			return (myCommand);
	}
	while (true)
	{
		if (pathEnvVar[i] == '\0' || pathEnvVar[i] == ':')
		{
			myEndPath = duplicatingMyChars(pathEnvVar, myCurrentPos, i);
			if (myEndPath == NULL)
				_strcat(myEndPath, myCommand);
			else
			{
				_strcat(myEndPath, "/");
				_strcat(myEndPath, myCommand);
			}
			if (isExecutable(myInfo, myEndPath) == true)
				return (myEndPath);
			if (pathEnvVar[i] == '\0')
				break;
			myCurrentPos = i;
		}
		i = i + 1;
	}
	return (NULL);
}
