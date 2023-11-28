#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* frees the given variable,
	if it exists and shifts all following variables one spot forward in envp */

void	remove_var(t_data *data, char *var_name)
{
	int	i;

	i = var_index(var_name, data->envp);
	if (i == -1)
		return ;
	free(data->envp[i]);
	while (data->envp[i])
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
}

/* always returns 0 and does not print error message */

int	builtin_unset(t_data *data)
{
	int i;

	i = 1;
	if (!data->cmd->args[1])
		return (0);
	while (data->cmd->args[i])
	{
		remove_var(data, data->cmd->args[i]);
		i++;
	}
	return (0);
}