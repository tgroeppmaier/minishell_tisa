#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* functions to change, or get data from the environment variables. We replace the env at the start of minishell
with dynamically allocated memory to change and free it later without issues. */

extern char	**environ; // we have to check, if we can use this approach to retriev env variables

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

int	free_envp(t_data *data)
{
	int	i;

	i = 0;
	if (!data->envp)
		return (1);
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	// data->envp = NULL;
	return (0);
}

	/* dynamically allocates memory and copies the given env into it and returns pointer to it */

char	**copy_environ(char **envp)
{
	int i = 0;
	char	**new_envp;

	new_envp = (char **)malloc((count_env(envp) + 1) * sizeof(char *));
	while(envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return(new_envp);
}

/* 		prints all environment variables to stdout. maybe use ft_putstr_fd? but if we redirect before calling
		it should not be necessary */

void builtin_env(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		ft_putstr(envp[i]);
		write(1, "\n", 1);
		i++;
	}
}

/* int main(int argc, char **argv, char **envp)
{
	char *var;
	char *args[] = {"/usr/bin/ls", "-la", NULL};
	char **new_envp;

	// printf("env test: %s\n", envp[36]);
	new_envp = copy_environ(envp);
	builtin_env(envp);
	// envp[36] = ft_strdup("TEST=test");
	// printf("env test: %s\n", new_envp[36]);
	free_envp(new_envp);
	// execve(args[0], args, envp);
	return(0);
} */

// char *get_env_var_value(char *var, char **env)
// {

// }
