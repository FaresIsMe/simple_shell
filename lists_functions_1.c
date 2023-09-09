#include "shell.h"

/**
 * print_list - A function that prints the elements of a linked list
 * @h: A pointer to the head of the linked list
 *
 * Return: It returns the number of elements in the linked list
*/

size_t print_list(const list_t *h)
{
	const list_t *myHead;
	size_t counter = 0;
	
	if (h == NULL)
		return (0);
	
	while (h != NULL)
	{
		if ((*myHead).str != NULL)
			_puts((myHead).str);
		else
			_puts("(nil)");
		_putchar('\n');
		myHead = myHead + 1;
		counter++;	
	}
	return (counter);
}



