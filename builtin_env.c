#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* functions to change,
	or get data from the environment variables. We replace the env at the start of minishell
with dynamically allocated memory to change and free it later without issues. */

int	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr(envp[i]);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		i++;
	}
	return (i);
}

/* dynamically allocates memory,
	copies the given env into it and returns pointer to it */

char	**copy_environ(char **envp, int additional_space)
{
	int		i;
	int		total_space;
	char	**new_envp;

	i = 0;
	total_space = count_env(envp) + additional_space + 1;
	new_envp = (char **)malloc(total_space * sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			free_envp(&new_envp);
			return (NULL);
		}
		i++;
	}
	while (i < total_space)
		new_envp[i++] = NULL;
	return (new_envp);
}

/* 		prints all environment variables to stdout. maybe use ft_putstr_fd? but if we redirect before calling
		it should not be necessary */

int	builtin_env(t_data *data)
{
	if (data->cmd->args[1] == NULL)
	{
		print_env(data->envp);
		return (0);
	}
	printf("env: '%s': No such file or directory\n", data->cmd->args[1]);
		// needs to be replaced with ft_printf
	return (127);
}
