#include "shell.h"

/**
 * print_list - A function that prints the elements of a linked list
 * @h: A pointer to the head of the linked list
 *
 * Return: It returns the number of elements in the linked list
*/

size_t print_list(const myList *h)
{
	const myList *current = h;
	size_t counter = 0;

	while (current != NULL)
	{
		if (current->myString != NULL)
			_puts(current->myString);
		else
			_puts("(nil)");
		_putchar('\n');
		current = current->next;
		counter++;
	}

	return (counter);
}

/**
 * addingNodeBeg - A function to add a node at the beginning of the
 * linked list
 * @myHead: A pointer to the head of the linked list
 * @myString: A pointer to the string that we want to put
 * in the linked list
 * @num: The number of the node in the history
 *
 * Return: NULL or a pointer to the newly created node
*/

myList *addingNodeBeg(myList **myHead, char *myString, int num)
{
	myList *newHead;

	if (myHead == NULL)
		return (NULL);
	newHead = malloc(sizeof(myList));
	if (newHead == NULL)
		return (NULL);
	_memset((void *)newHead, 0, sizeof(myList));
	(*newHead).theNum = num;
	if (myString != NULL)
	{
		(*newHead).myString = _strdup(myString);
		if ((*newHead).myString == NULL)
		{
			free(newHead);
			return (NULL);
		}
	}
	(*newHead).next = *myHead;
	*myHead = newHead;
	return (newHead);
}

/**
 * add_node_end - A function to add a node at the end
 * @head: A pointer to the pointer who points at the first node
 * @str: A string the should be inputed into the newly created node
 * @num: The number of the node in the history
 * Return: It returns a pointer to the newly created node
*/

myList *add_node_end(myList **head, char *str, int num)
{
	myList *newNode = (myList *)malloc(sizeof(myList));
	myList *current;

	if (newNode == NULL || head == NULL)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(newNode));
	(*newNode).theNum = num;
	if (str != NULL)
	{
		newNode->myString = _strdup(str);
		if (newNode->myString == NULL)
		{
			free(newNode);
			return (NULL);
		}
		newNode->next = NULL;
	}
	if (!*head)
	{
		*head = newNode;
		return (newNode);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = newNode;
	return (newNode);
}


/**
 * delete_node_at_index - A function to delete a node at
 * a specific index
 * @head: A pointer to a pointer that points to the head
 * of the linked list
 * @index: The index of the node to be deleted
 *
 * Return: 1 or -1
*/

int delete_node_at_index(myList **head, unsigned int index)
{
	myList *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->myString);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->myString);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - A function to free the linked list
 * @head: A pointer to a pointer that
 * points to the head of the linked list
 *
 * Return: It returns nothing (void)
*/

void free_list(myList **head)
{
	myList *current = *head;
	myList *next;

	if (head == NULL || *head == NULL)
		return;
	while (current != NULL)
	{
		next = current->next;
		free(current->myString);
		free(current);
		current = next;
	}
	*head = NULL;
}
