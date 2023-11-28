#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* functions to change, or get data from the environment variables. We replace the env at the start of minishell
with dynamically allocated memory to change and free it later without issues. */

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

void free_envp(char ***envp) 
{
    int i = 0;

    if (!(*envp))
        return;
    while ((*envp)[i]) 
	{
        free((*envp)[i]);
        i++;
    }
    free(*envp);
    *envp = NULL;  // Set the original envp pointer to NULL
}

/* dynamically allocates memory, copies the given env into it and returns pointer to it */

char	**copy_environ(char **envp, int additional_space)
{
	int i = 0;
	int total_space;
	char	**new_envp;

	total_space = count_env(envp) + additional_space + 1;
	new_envp = (char **)malloc(total_space * sizeof(char *));
	if(!new_envp)
		return(NULL);
	while(envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if(new_envp[i] == NULL)
		{
			free_envp(&new_envp);
			return(NULL);
		}
		i++;
	}
	while(i < total_space)
		new_envp[i++] = NULL;
	return(new_envp);
}

/* 		prints all environment variables to stdout. maybe use ft_putstr_fd? but if we redirect before calling
		it should not be necessary */

int builtin_env(t_data *data)
{
	int i;

	i = 0;
	if(data->cmd->args[1] == NULL)
	{
		while(data->envp[i])
		{
			ft_putstr(data->envp[i]);
			write(1, "\n", 1);
			i++;
		}
		return(0);
	}
	printf("env: '%s': No such file or directory\n", data->cmd->args[1]); // needs to be replaced with ft_printf
	return(127);
}

