#include "shell.h"

/**
 * main - entry
 * @avrgv: The vector arguement
 * @argc: The count arguement
 *
 * Return: 0 on success, 1 on failure
*/

int main(int argc, char **argv)
{
	myInfoObject INFO [] = { Iintializing_INFO };
	int file_descriptor = 2;

	asm (
		"mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor)
	);

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
		exit(126);
			if (errno == ENOENT)
			{
				_puts(argv[0]);
				_puts(": 0; Can't open");
				_puts(argv[1]);
				_putchar('\n');
				_putchar(BUFFER_FLUSH_CONDITION);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		INFO->read_file_descriptor = file_descriptor;
	}

	makingtheLinkedList(INFO);
	ReadHistoryList(INFO);
	her_shell_hell(INFO, argv);

	return (EXIT_SUCCESS);
}
