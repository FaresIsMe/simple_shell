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

char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_del(str[i], d) && (is_del(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_del(str[i], d))
			i++;
		k = 0;
		while (!is_del(str[i + k], d) && str[i + k])
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
