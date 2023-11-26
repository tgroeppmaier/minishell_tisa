#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

/* Funtion to check, if the -n option is set with echo (no trailing newline after echo print) */

static bool	check_n(char *word)
{
	int	i;

	i = 1;
	if (word[0] == '-')
	{
		while (word[i])
		{
			if (word[i] != 'n')
				return (false);
			i++;
		}
	}
	if (word[1] != 'n') // checks for special case, where word is "-"
		return (false);
	else
		return (true);
}

/* it does not check if words[0] == NULL because,
	when this function gets called, words[0] should be echo. words should be the command line, separated into words */

int	builtin_echo(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[i] && check_n(args[i]) == true)
	{
		i++;
	}
	while (args[i])
	{
		ft_putstr(args[i]);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (check_n(args[1]) == false)
		write(1, "\n", 1);
	return (0);
}
