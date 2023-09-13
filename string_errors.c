#include "shell.h"

/**
 * put_fd - writes c to the file_descriptor given
 * @c: The charcter to be printe
 * @file_descriptor: the file to write to
 *
 * Return: 1 on success, -1 on failure
*/
int put_fd(char c, int file_descriptor)
{
	static int i;
	static char buffer[MAX_BUFFER_SIZE];

	if (c == BUFFER_FLUSH_CONDITION || MAX_BUFFER_SIZE <= i)
	{
		write(file_descriptor, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH_CONDITION)
	{
		buffer[i++] = c;
	}
	return (1);
}
/**
 *  _puts_fd - like _puts it uses put_fd to write to the file
 * @string: The string
 * @file_descriptor: The file to write to
 *
 * Return: The number of characters
*/

int _puts_fd(char *string, int file_descriptor)
{
	int i = 0;

	if (string == NULL)
	return (0);

	while (*string != NULL)
	i = i + put_fd(string, file_descriptor);

	return (i);
}