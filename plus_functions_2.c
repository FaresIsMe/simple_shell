#include "shell.h"

/**
 * printingErrors - A function to print error on the terimanl
 * (stderr)
 * @myInfo: A pointer to myInfo variable
 * @myError: A pointer to string that cointains
 * the error string
 * 
 * Return: Nothing (void)
*/

void printingErrors(myInfoObject *myInfo, char *myError)
{
	_puts_fd((*myInfo).filename, STDERR_FILENO);
	_puts_fd(": ", STDERR_FILENO);
	printingDecimal((*myInfo).line_count, STDERR_FILENO);
	_puts_fd(": ", STDERR_FILENO);
	_puts_fd((*myInfo).arguments[0], STDERR_FILENO);
	_puts_fd(": ", STDERR_FILENO);
	_puts_fd(myError, STDERR_FILENO);
}

/**
 * convertor - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convertor(long int num, int myBase, int myFlags)
{
	char numbersArray[40];
	static char myBuffer[50];
	char theSign = 0;
	char *ptr;
	unsigned long conditionNum = num;

	if (!(myFlags & IS_UNSIGNED) && num < 0)
	{
		conditionNum = -1 * num;
		theSign = '-';
	}
	if (myFlags & IS_LOWERCASE)
		_strcpy(numbersArray, "0123456789abcdef");
	else
		_strcpy(numbersArray, "0123456789ABCDEF");

	ptr = &myBuffer[49];
	*ptr = '\0';
	do {
		ptr = ptr - 1;
		*ptr = numbersArray[conditionNum % myBase];
		conditionNum = conditionNum / myBase;
	} while(conditionNum);

	if (theSign != 0)
	{
		ptr = ptr - 1;
		*ptr = theSign;
	}
	return (ptr);
}

/**
 * removingComments - A function to remove comments from a buffer
 * passed to it
 * @myBuffer: A Pointer to string which is the buffer
 * 
 * echo "My name is Amr" # (example)
 * #echo "My name is Amr"
 * Return: Nothing (void) 
*/

void removingComments(char *myBuffer)
{
	int theLooperF;

	for (theLooperF = 0; *(myBuffer + theLooperF) != '\0'; theLooperF++)
	{
		if (*(myBuffer + theLooperF)  == '#'
		&& (theLooperF == 0 || myBuffer[theLooperF- 1] == ' '))
		{
			*(myBuffer + theLooperF) = '\0';
		break;   
		}
	}
}

/**
 * errorToInteger - A function to convert an error to integer
 * @myError: A pointer to a string that represnts
 * the error
 * 
 * Return: 0 on Success and -1 on Failure
*/

int errorToInteger(char *myError)
{
	int AmrLooper = 0;
	unsigned long int finalResult = 0;

	if (*myError == '+')
		myError = myError + 1;
	for (AmrLooper; myError[AmrLooper]; AmrLooper++)
	{
		if(myError[AmrLooper] >= '0' && myError[AmrLooper] <= '9')
		{
			finalResult = finalResult * 10 + (myError[AmrLooper] - '0');
			if (finalResult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (finalResult);
}
