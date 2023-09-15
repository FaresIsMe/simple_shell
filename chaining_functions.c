#include "shell.h"


/**
 * isThereChaining - A function to check if there is chaining in
 * the command or not
 * @myInfo: A variable that stores all the information about the
 * command
 * @myBuffer: A pointer to a string that stores the command
 * @FaresPos: The position in which we're searching for
 * a chaining
 *
 * Return: 0 on no chaining and 1 on there is chaning
*/

bool isThereChaining(myInfoObject *myInfo, char *myBuffer, int *FaresPos)
{
	int tempFarsePos = *FaresPos;
	bool isChaining = false;

	switch (myBuffer[tempFarsePos])
	{
		case '|':
			if (myBuffer[tempFarsePos + 1] == '|')
			{
				myBuffer[tempFarsePos] = '\0';
				tempFarsePos = tempFarsePos + 1;
				(*myInfo).command_buffer_type = OR_COMMAND;
				isChaining = true;
			}
			break;
		case '&':
			if (myBuffer[tempFarsePos + 1] == '&')
			{
				myBuffer[tempFarsePos] = '\0';
				tempFarsePos = tempFarsePos + 1;
				(*myInfo).command_buffer_type = AND_COMMAND;
				isChaining = true;
			}
			break;

		case ';':
			myBuffer[tempFarsePos] = '\0';
			(*myInfo).command_buffer_type = CHAIN_COMMAND;
			isChaining = true;
			break;
	}

	if (isChaining)
		*FaresPos = tempFarsePos;

	return (isChaining);
}

/**
 * cSWC - A function to check some conditions about || and &&
 * @myI: A pointer to myInfoObject variable that contains
 * everything about the shell currently
 * @myBuf: A pointer to a buffer
 * @myPo: A pointer that points to the place that
 * we're now on the command
 * @i: The beginning of the buffer
 * @myLen: The length of the buffer
 *
 * Return: Nothing (void)
*/


void cSWC(myInfoObject *myI, char *myBuf, size_t *myPo, size_t i, size_t myLen)
{
	size_t amrCounter = *myPo;

	if (myI->command_buffer_type == AND_COMMAND && myI->status)
	{
		myBuf[i] = '\0';
		amrCounter = myLen;
	}
	else if (myI->command_buffer_type == OR_COMMAND && myI->status == 0)
	{
		myBuf[i] = '\0';
		amrCounter = myLen;
	}

	*myPo = amrCounter;
}

/**
 * replacingNewandOldStrings - A function to replace strings
 * @theOldOne: A pointer to a pointer that points
 * to the old string
 * @theNewOne: A pointer that points to the new string
 *
 * Return: True
*/

bool replacingNewandOldStrings(char **theOldOne, char *theNewOne)
{
	free(*theOldOne);
	*theOldOne = theNewOne;
	return (true);
}