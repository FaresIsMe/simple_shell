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
    static size_t buffer_pos = 0, buffer_len = 0;
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
            _strncat(line, buffer + buffer_pos, newline_pos - (buffer + buffer_pos) + 1);
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
    return (line_len == 0 && read_len == 0 ? -1 : line_len);
}


