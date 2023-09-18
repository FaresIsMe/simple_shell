#include "shell.h"

/**
 * handle_sigin - no ctrl+C
 * @empty: unused
 *
 * Return: nothing
*/
void handle_sigin(__attribute__((unused))int empty)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH_CONDITION);
}

/**
 * her_shell_hell - Most of the functions are here, The main Loop
 * @shellInfo: A pointer to myInfoObject that contains everythin
 * @arguments: The arguments vector passed from the main function
 *
 * Return: 0 on success, The error number on failure
*/

int her_shell_hell(myInfoObject *shellInfo, char *arguments[])
{
	int builtinResult = 0;
	ssize_t read_status = 0;

	if (isInteractive(shellInfo) == 0 && shellInfo->status)
		exit(shellInfo->status);

	if (builtinResult == -2)
	{
		if (shellInfo->error_number == -1)
			exit(shellInfo->status);
	}

	while (read_status != -1 && builtinResult != -2)
	{
		clearMyInfoVariable(shellInfo);
		if (isInteractive(shellInfo) != 0)
			_puts("$ ");

		read_status = GetInput(shellInfo);
		if (read_status != -1)
		{
			settingMyInfoVariable(shellInfo, arguments);
			builtinResult = findingMyBuiltinFunc(shellInfo);
			if (builtinResult == -1)
				findingCommandLastTime(shellInfo);
		}
		else if (isInteractive(shellInfo))
			_putchar('\n');

		freeMyInfo(shellInfo, 0);
	}

	WriteHistory(shellInfo);
	freeMyInfo(shellInfo, 1);

	return (builtinResult);
}

/**
 * ReadBuffer  -  function reads data from a file descriptor into a buffer
 * @myInfo: idk
 * @buffer: The buffer
 * @i: idfk
 *
 *Return: the read size in bytes
*/
ssize_t ReadBuffer(myInfoObject *myInfo, char *buffer, size_t *i)
{
	ssize_t read_val = 0;

	if (*i == 0)
	{
		read_val = read(myInfo->read_file_descriptor, buffer, MAX_BUFFER_SIZE);
		if (read_val >= 0)
			*i = read_val;
	}
	return (read_val);
}
/**
 * GetInput - gets a line but without the new line
 * @myInfo: Hi again, it's me
 *
 * Return: The size of the read file
*/

ssize_t GetInput(myInfoObject *myInfo)
{
	static char *commandChainBuffer;
	static size_t currentPosition, nextPosition, bufferLength;
	ssize_t bytesRead = 0;
	char **currentCommand = &(myInfo->argument), *currentPositionPtr;

	_putchar(BUFFER_FLUSH_CONDITION);
	bytesRead = InputBuffer(myInfo, &commandChainBuffer, &bufferLength);
	if (bytesRead == -1)
		return (-1);

	if (bufferLength)
	{
		nextPosition = currentPosition;
		currentPositionPtr = commandChainBuffer + currentPosition;
		cSWC(myInfo, commandChainBuffer,
		&nextPosition, currentPosition, bufferLength);
		while (nextPosition < bufferLength &&
		!isThereChaining(myInfo, commandChainBuffer, &nextPosition))
			nextPosition++;

		currentPosition = nextPosition + 1;

		if (currentPosition >= bufferLength)
		{
			currentPosition = bufferLength = 0;
			myInfo->command_buffer_type = NORM_COMMAND;
		}

		*currentCommand = currentPositionPtr;
		return (_strlen(currentPositionPtr));
	}

	*currentCommand = commandChainBuffer;
	return (bytesRead);
}
/**
 * InputBuffer - chained buffer commands
 * @myInfo: struct parameter
 * @buffer: buffer's address
 * @length: address of the variable length
 *
 * Return: size of bytes read.
*/
ssize_t InputBuffer(myInfoObject *myInfo, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t newLength = 0;

	if (*length == 0)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigin);
#if USE_GETLINE
		bytesRead = getline(buffer, &newLength, stdin);
#else
		bytesRead = _getline(myInfo, buffer, &newLength);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			myInfo->linecount_flag = 1;
			removingComments(*buffer);
			BuildHistoryList(myInfo, *buffer, myInfo->history_count++);

			if (_strchr(*buffer, ';'))
			{
				*length = bytesRead;
				myInfo->command_buffer = buffer;
			}
		}
	}
	return (bytesRead);
}
