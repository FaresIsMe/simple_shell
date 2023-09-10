#include "shell.h"

/**
 * strtow2 - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char *del)
{
	if (str == NULL || del == NULL)
		return (NULL);

	int i, j, k, n, m , count = 0;
	char **words = NULL;

	n = _strlen(str);
	m = _strlen(del);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (str[i] == del[j])
				break;
		}
		if (j == m && (i == 0 || j != m - 1 && str[i - 1] == del[m - 1]))
			count++;
	}


	words = (char **) malloc((count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);

	for (i = 0, j = 0; i < n && j < count; i++)
	{
		for (k = 0; k < m; k++)
		{
			if (str[i] == del[k])
				break;
		}
		if (k == m && (i == 0 || k != m - 1 && str[i - 1] == del[m - 1]))
		{
			int len = i - j;
			words[j] = (char *) malloc((len + 1) * sizeof(char));
			if (words[j] == NULL)
				return (NULL);
			_strncpy(words[j], str + j, len);
			words[j][len] = '\0';
			j++;
		}
	}
	words[count] = NULL;

	return (words);
}


/**
 * is_del - checks if a character is a delimiter
 * @c: the character to check
 * @del: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_del(char c, char *del)
{
	while (*del != '\0')
	{
		if (c == *del)
			return (1);
		del++;
	}
	return (0);
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *del)
{
	char **words = NULL;
	int num_words = 0, str_len, del_len, word_start, word_len;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (del == NULL)
		del = " ";

	str_len = _strlen(str);
	del_len = _strlen(del);

	int i = 0;
	while (i < str_len)
	{
		while (i < str_len && is_del(str[i], del))
			i++;

		if (i == str_len)
			break;

		word_start = i;
		while (i < str_len && !is_del(str[i], del))
			i++;

		int word_len = i - word_start;
		num_words++;

		words = _realloc(words, num_words * sizeof(char *));
		words[num_words - 1] = malloc((word_len + 1) * sizeof(char));
		_strncpy(words[num_words - 1], str + word_start, word_len);
		words[num_words - 1][word_len] = '\0';
	}

	if (num_words == 0)
	{
		free(words);
		return (NULL);
	}

	words = _realloc(words, (num_words + 1) * sizeof(char *));
	words[num_words] = NULL;

	return (words);
}