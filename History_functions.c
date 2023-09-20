#include "shell.h"
/**
 * GetHistoryFile - get history file
 * @myInfo: smth in a struct we made
 *
 * Return: history file
*/
char *GetHistoryFile(myInfoObject *myInfo)
{
	char *history_file = NULL;
	char *home_dir;
	size_t dir_len, file_len;

	home_dir = gettingEnviormentVariable(myInfo, "HOME=");

	if (home_dir)
	{
		dir_len = _strlen(home_dir);
		file_len = _strlen(HISTORY_FILE);
		history_file = malloc(sizeof(char) * (dir_len + file_len + 2));

		if (history_file)
		{
			_strcpy(history_file, home_dir);
			_strcat(history_file, "/");
			_strcat(history_file, HISTORY_FILE);
		}
	}
	return (history_file);
}
/**
 *WriteHistory - writes in a history file it created or it existed
 *@myInfo: اهلا بيك في مصر
 *
 *
 *Return: 1 on success
*/
int WriteHistory(myInfoObject *myInfo)
{
	int file_descriptor;
	char *filename;
	myList *current_node = NULL;

	filename = GetHistoryFile(myInfo);

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(filename);

	if (file_descriptor == -1)
	return (-1);

	for (current_node = myInfo->history; current_node;
	current_node = current_node->next)
	{
		_puts_fd(current_node->myString, file_descriptor);
		put_fd('\n', file_descriptor);
	}

	put_fd(BUFFER_FLUSH_CONDITION, file_descriptor);
	close(file_descriptor);

	return (1);
}
/**
 * BuildHistoryList - adds enrty to linked list
 * @myInfo: I DON"T GIVE A FART
 * @buffer: idc
 * @linecount: stll dc
 *
 * Return: 0
*/
int BuildHistoryList(myInfoObject *myInfo, char *buffer, int linecount)
{
	myList *newnode = NULL;

	if (myInfo->history)
	newnode = myInfo->history;

	add_node_end(&newnode, buffer, linecount);

	if (!myInfo->history)
	myInfo->history = newnode;

	return (0);
}
/**
 * REM_History - Renumber the history linked list after changes
 * @myInfo: stfu
 *
 * Return: new history count
*/
int REM_History(myInfoObject *myInfo)
{
	myList *current_node = myInfo->history;
	int new_histcount = 0;

	while (current_node)
	{
		current_node->theNum = new_histcount++;
		current_node = current_node->next;
	}

	myInfo->history_count = new_histcount;
	return (new_histcount);
}

/**
 * ReadHistoryList - whatever
 * @myInfo: whatever
 *
 * Return: SUCK YOUR MOM
 *
*/

int ReadHistoryList(myInfoObject *myInfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = GetHistoryFile(myInfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			BuildHistoryList(myInfo, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		BuildHistoryList(myInfo, buf + last, linecount++);
	free(buf);
	myInfo->history_count = linecount;
	while (myInfo->history_count-- >= 4096)
		delete_node_at_index(&(myInfo->history), 0);
	REM_History(myInfo);
	return (myInfo->history_count);
}
