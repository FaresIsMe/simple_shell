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

char **strtow(char *str, char *del)
{
	char **words = NULL;
	int num_words = 0, str_len, del_len, word_start, i = 0, word_len, j;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (del == NULL)
		del = " ";
	str_len = _strlen(str);
	del_len = _strlen(del);
	(void)del_len;
	while (i < str_len)
	{
		while (i < str_len && is_del(str[i], del))
			i++;
		if (i == str_len)
			break;
		word_start = i;
		while (i < str_len && !is_del(str[i], del))
			i++;
		word_len = i - word_start;
		num_words++;
		words = _realloc(words, num_words * sizeof(char *),
						 (num_words + 1) * sizeof(char *));
		if (words == NULL)
		{
			for (j = 0; j < num_words - 1; j++)
				free(words[j]);
			free(words);
			return (NULL);
		}
		words[num_words - 1] = malloc((word_len + 1) * sizeof(char));
		if (words[num_words - 1] == NULL)
		{
			for (j = 0; j < num_words - 1; j++)
				free(words[j]);
			free(words);
			return (NULL);
		}
		_strncpy(words[num_words - 1], str + word_start, word_len);
		words[num_words - 1][word_len] = '\0';
	}
	if (num_words == 0)
	{
		free(words);
		return (NULL);
	}
	words = _realloc(words, (num_words + 1) * sizeof(char *),
					 (num_words + 1) * sizeof(char *));
	if (words == NULL)
	{
		for (j = 0; j < num_words; j++)
			free(words[j]);
		free(words);
		return (NULL);
	}
	words[num_words] = NULL;
	return (words);
}
