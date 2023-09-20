#include "shell.h"
/**
 * strtow2 - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
*/

char **strtow2(char *str, char *del)
{
    int i, j, k, n, m, count = 0, len = 0, l;
    char **words = NULL;

    if (str == NULL || del == NULL)
        return (NULL);
    n = _strlen(str);
    m = _strlen(del);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (str[i] == del[j])
                break;
        }
        if (j == m && (i == 0 || (j != m - 1 && str[i - 1] == del[m - 1])))
            count++;
    }
    words = (char **)malloc((count + 1) * sizeof(char *));
    if (words == NULL)
        return (NULL);
    for (i = 0, j = 0; i < n && j < count; i++)
    {
        for (k = 0; k < m; k++)
        {
            if (str[i] == del[k])
                break;
        }
        if (k == m && (i == 0 || (k != m - 1 && str[i - 1] == del[m - 1])))
        {
            len = i - j;
            words[j] = (char *)malloc((len + 1) * sizeof(char));
            if (words[j] == NULL)
            {
                for (l = 0; l < j; l++)
                    free(words[l]);
                free(words);
                return (NULL);
            }
            _strncpy(words[j], str + j, len);
            words[j][len] = '\0';
            j++;
        }
    }
    words[count] = NULL;
    return (words);
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *delimiter)
{
	int index_i, index_j, index_k, index_m, word_count = 0;
	char **result;

	if (str == NULL || str[0] == 0)
		return NULL;
	if (!delimiter)
		delimiter = " ";
	for (index_i = 0; str[index_i] != '\0'; index_i++)
		if (!is_delimiter(str[index_i], delimiter) &&
        (is_delimiter(str[index_i + 1], delimiter) || !str[index_i + 1]))
			word_count++;

	if (word_count == 0)
		return NULL;
	result = malloc((1 + word_count) * sizeof(char *));
	if (!result)
		return NULL;
	for (index_i = 0, index_j = 0; index_j < word_count; index_j++)
	{
		while (is_delimiter(str[index_i], delimiter))
			index_i++;
		index_k = 0;
		while (!is_delimiter(str[index_i + index_k],
        delimiter) && str[index_i + index_k])
			index_k++;
		result[index_j] = malloc((index_k + 1) * sizeof(char));
		if (!result[index_j])
		{
			for (index_k = 0; index_k < index_j; index_k++)
				free(result[index_k]);
			free(result);
			return NULL;
		}
		for (index_m = 0; index_m < index_k; index_m++)
			result[index_j][index_m] = str[index_i++];
		result[index_j][index_m] = 0;
	}
	result[index_j] = NULL;
	return result;
}
