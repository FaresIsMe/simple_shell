#include "shell.h"
/**
 * strtow2 - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
*/

char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delimiter: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *delimiter)
{
	int index_i, index_j, index_k, index_m, word_count = 0;
	char **result;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (index_i = 0; str[index_i] != '\0'; index_i++)
		if (!is_del(str[index_i], delimiter) &&
		(is_del(str[index_i + 1], delimiter) || !str[index_i + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	result = malloc((1 + word_count) * sizeof(char *));
	if (!result)
		return (NULL);
	for (index_i = 0, index_j = 0; index_j < word_count; index_j++)
	{
		while (is_del(str[index_i], delimiter))
			index_i++;
		index_k = 0;
		while (!is_del(str[index_i + index_k],
		delimiter) && str[index_i + index_k])
			index_k++;
		result[index_j] = malloc((index_k + 1) * sizeof(char));
		if (!result[index_j])
		{
			for (index_k = 0; index_k < index_j; index_k++)
				free(result[index_k]);
			free(result);
			return (NULL);
		}
		for (index_m = 0; index_m < index_k; index_m++)
			result[index_j][index_m] = str[index_i++];
		result[index_j][index_m] = 0;
	}
	result[index_j] = NULL;
	return (result);
}
