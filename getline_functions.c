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
 * _getline - gets the line from standard input
 * @myInfo: I don't know man leave me alone
 * @ptr: address of pointer to buffer
 * @length: The size of a preallocated pointer buffer
 *
 * Return: lots of things I don't care
 */
int _getline(myInfoObject *myInfo, char **ptr, size_t *length)
{
	static char buffer[MAX_BUFFER_SIZE];
	static size_t index, buffer_length;
	size_t count;
	ssize_t read_result = 0, seek_result = 0;
	char *pointer = NULL, *new_pointer = NULL, *character;

	pointer = *ptr;
	if (pointer && length)
		seek_result = *length;
	if (index == buffer_length)
		index = buffer_length = 0;

	read_result = ReadBuffer(myInfo, buffer, &buffer_length);
	if (read_result == -1 || (read_result == 0 && buffer_length == 0))
		return (-1);

	character = _strchr(buffer + index, '\n');
	count = character ? 1 + (unsigned int)(character - buffer) : buffer_length;
	new_pointer = realloc(pointer, 
 	seek_result ? seek_result + count : count + 1);

	if (!new_pointer)
		return (pointer ? free(pointer), -1 : -1);

	if (seek_result)
		_strncat(new_pointer, buffer + index, count - index);
	else
		_strncpy(new_pointer, buffer + index, count - index + 1);

	seek_result += count - index;
	index = count;
	pointer = new_pointer;

	if (length)
		*length = seek_result;
	*ptr = pointer;
	return (seek_result);
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
