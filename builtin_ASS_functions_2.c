#include "shell.h"

/**
 * print_history - for real?
 * @game_of_thrones: good series
 *
 * Return: 0 after printing
*/
int print_history(myInfoObject *game_of_thrones)
{
	printingTheList(game_of_thrones->history);
	return (0);
}
/**
 * _unset_alias - it unsets an alias to be changed or whatever
 * @die: die
 * @dying: good
 *
 * Return: eminem
*/
int _unset_alias(myInfoObject *die, char *dying)
{
	int eminem;
	char *amr, fares;

	amr = _strchr(dying, '=');

	if (amr == NULL)
	return (1);

	fares = amr;
	*amr = '\0';

	eminem = DeleteNodeIndex(&(die->alias),
		gettingTheIndex(die->alias, isNodeStartsWith(die->alias, dying, -1)));

	*amr = fares;

	return (eminem);
}
/**
 * _set_alias - -_-
 * @help: me for real.
 * @me: not him.
 *
 * Return: 1; otherwise, it returns 0.
*/
int _set_alias(myInfoObject *help, char *me)
{
	char *equal_sign, *alias_value;

	equal_sign = _strchr(me, '=');
	if (equal_sign == NULL)
	return (1);   /*why 1? no idea but wtver*/

	alias_value = equal_sign + 1;

	if (*alias_value == NULL)
	return (_unset_alias(help, me));

	_unset_alias(help, me);
	return (add_node_end(&(help->alias), me, 0) == NULL);
}
/**
 * PrintAlias - prints alias
 * @pain: good name
 *
 * Return: 0 on success, 1 on error.
*/
int PrintAlias(myList *pain)
{
	char *fares = NULL, *amr = NULL; /*as always my friend we are null :(*/

	if (!pain)
	return (1);

	fares = _strchr(pain->myString, '=');

	amr = pain->myString;
	while (amr <= fares)
	{
		_putchar(*amr);
		amr++;
	}
		_putchar('\'');
		_puts(fares + 1);
		_puts("'\n");
		return (0);
}
/**
 *man_alias - man alias and shit
 * @myInfo: f*ck off
 *
 * Return: zero.
*/
int man_alias(myInfoObject *myInfo)
{
		int i = 0;
	char *pain = NULL;
	myList *node = NULL;

	if (myInfo->argument_count == 1)
	{
		node = myInfo->alias;
		while (node)
		{
			PrintAlias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; myInfo->arguments[i]; i++)
	{
		pain = _strchr(myInfo->arguments[i], '=');
		if (pain)
			_set_alias(myInfo, myInfo->arguments[i]);
		else
			PrintAlias(isNodeStartsWith(myInfo->alias, myInfo->arguments[i], '='));
	}
	return (0);
}
