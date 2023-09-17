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
 * @lineptr: address of pointer to buffer
 * @n: The size of a preallocated pointer buffer
 *
 * Return: lots of things I don't care
 */
int _getline(myInfoObject *myInfo, char **lineptr, size_t *n)
{
	static char buffer[MAX_BUFFER_SIZE];
	static size_t buffer_pos, buffer_len;
	size_t line_len = 0;
	ssize_t read_len = 0;
	char *line = NULL, *new_line = NULL, *newline_pos = NULL;

	line = *lineptr;
	if (line && n)
		line_len = *n;
	if (buffer_pos == buffer_len)
	{
		buffer_pos = 0;
		buffer_len = 0;
	}
	while (1)
	{
		if (buffer_pos == buffer_len)
		{
			read_len = read(myInfo->read_file_descriptor, buffer, MAX_BUFFER_SIZE);
			if (read_len == -1)
				return (-1);
			if (read_len == 0)
				break;
			buffer_len = read_len;
			buffer_pos = 0;
		}
		newline_pos = memchr(buffer + buffer_pos, '\n', buffer_len - buffer_pos);
		if (newline_pos)
		{
			line_len += newline_pos - (buffer + buffer_pos) + 1;
			new_line = _realloc(line, line_len, line_len);
			if (!new_line)
				return (line ? free(line), -1 : -1);
			line = new_line;
			*lineptr = line;
			_strncat(line, buffer + buffer_pos,
			newline_pos - (buffer + buffer_pos) + 1);
			buffer_pos = newline_pos - buffer + 1;
			break;
		}
		line_len += buffer_len - buffer_pos;
		new_line = realloc(line, line_len + 1);
		if (!new_line)
			return (line ? free(line), -1 : -1);
		line = new_line;
		*lineptr = line;
		strncat(line, buffer + buffer_pos, buffer_len - buffer_pos);
		buffer_pos = buffer_len;
	}
	if (n)
		*n = line_len;
	line[line_len] = '\0';
	return (line_len == 0 && read_len == 0 ? -1 : (int)line_len);
}

/**
 * read_buf  -  function reads data from a file descriptor into a buffer
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
