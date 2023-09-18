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

/**
 * _getline - gets the line from standard input
 * @myInfo: I don't know man leave me alone
 * @lineptr: address of pointer to buffer
 * @n: The size of a preallocated pointer buffer
 *
 * Return: lots of things I don't care
 */
int _getline(myInfoObject *info, char **ptr, size_t *length)
{
	static char buf[MAX_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = ReadBuffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}