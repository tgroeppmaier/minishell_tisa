#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

/* Funtion to check, if the -n option is set with echo (no trailing newline after echo print) */

bool	check_n(char *word)
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

int	builtin_echo(char **words)
{
	int	i;

	i = 1;
	if (!words[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (words[i] && check_n(words[i]) == true)
	{
		i++;
	}
	while (words[i])
	{
		ft_putstr(words[i]);
		i++;
		if (words[i])
			write(1, " ", 1);
	}
	if (check_n(words[1]) == false)
		write(1, "\n", 1);
	return (0);
}

/* just for testing purposes, has leaks */

int	main(void)
{
	char *input;
	char **words;

	while (1)
	{
		input = readline("built_ins $ ");
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		else if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		words = ft_split(input, ' ');
		builtin_echo(words);
		add_history(input);
	}
	return (0);
}