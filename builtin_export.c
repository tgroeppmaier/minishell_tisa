#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* variables exported just with varname and no value dont appear in env until they get a value assigned to it.
	They appear when command export is run without arguments. Export of multiple variables at once is possible*/

void	free_data_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd->args[i])
	{
		free(data->cmd->args[i]);
		i++;
	}
	free(data->cmd->args);
	data->cmd->args = NULL;
}

/* var_name is a variable in env, it returns the index of it. If not, it returns
	-1 */

bool	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(envp[i]);
		write(1, "\n", 1);
		i++;
	}
	return (true);
}

/* adds variable if there is an '=' after var_name */

void add_var(char *var_name, t_data *data)
{
	int		i;
	char	**new_envp;

	data->exit_code = 1;
	i = count_env(data->envp);
	if (ft_strchr(var_name, '=') == NULL)
		return ;
	new_envp = copy_environ(data->envp, 1);
	if (!new_envp)
		return ;
	new_envp[i] = ft_strdup(var_name);
	if(!new_envp[i])
	{
		free_envp(&new_envp);
		return;
	}
	new_envp[i + 1] = NULL;
	free_envp(&(data->envp));
	data->envp = new_envp;
	data->exit_code = 0;
}

/*  returns index of given env variable, or -1 if its not found in env.
	can take only varname or varname=value */

int	var_index(char *var_name, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (var_name[len])
	{
		if (var_name[len] == '=')
			break ;
		len++;
	}
	while (envp[i])
	{
		if ((ft_strncmp(var_name, envp[i], len) == 0) && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/* variable name can only start with a-z, A-Z or '_' and can only contain a-z,
	A-Z, 0-9 and '_'  */

bool	is_valid_name(char *var_name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
	{
		return (false);
	}
	while (var_name[i] != '\0')
	{
		if (var_name[i] == '=')
			return (true);
		if (!ft_isalpha(var_name[i]) && !ft_isdigit(var_name[i]) && var_name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/* takes variable + value and updates env */

void update_var(char *var_name, t_data *data)
{
	int	i;

	i = var_index(var_name, data->envp);
	free(data->envp[i]);
	data->envp[i] = ft_strdup(var_name);
	if(!data->envp[i])
	{
		free(data->envp[i]);
		data->exit_code = 1;
		return ;
	}
	data->exit_code = 0;
}


/* checks, if the variable already exists in env. to be in env, it has to have a '='  */

bool	does_var_exist(char *var_name, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (var_name[len] && var_name[len] != '=')
		len++;
	if(var_name[len] != '=')
		return(false);
	while (envp[i])
	{
		if ((ft_strncmp(var_name, envp[i], len) == 0) && envp[i][len] == '=')
			return (true);
		i++;
	}
	return (false);
}

/* example for command: command[0] = "export", command[1] = 'VAR_NAME=value'  */

bool	builtin_export(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[0], "export") == 0 && args[1] == NULL) // just prints env
		return (print_export(data->envp));
	while (args[i])
	{
		if (!is_valid_name(args[i]))
		{

			printf("bash: export: '%s': not a valid identifier\n", args[i]);  // needs to be replaced with ft_printf
			data->exit_code = 1;
			return (false);
		}
		if (!does_var_exist(args[i], data->envp))
			add_var(args[i], data);
		else
			update_var(args[i], data);
		i++;
	}
	return (true);
}
