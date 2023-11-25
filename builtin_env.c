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

	/* dynamically allocates memory and copies the given env into it and returns pointer to it */

char	**copy_environ(char **envp)
{
	int i = 0;
	char	**new_envp;

	new_envp = (char **)malloc((count_env(envp) + 1) * sizeof(char *));
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
	new_envp[i] = NULL;
	return(new_envp);
}

/* 		prints all environment variables to stdout. maybe use ft_putstr_fd? but if we redirect before calling
		it should not be necessary */

void builtin_env(char **envp, t_data *data)
{
	int i;

	i = 0;
	while(envp[i])
	{
		ft_putstr(envp[i]);
		write(1, "\n", 1);
		i++;
	}
	data->exit_code = 0;
}

