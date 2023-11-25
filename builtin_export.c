#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* variables exported just with varname and no value dont appear in env until they get a value assigned to it.
	They appear when command export is run without arguments. so we need a separate data structure for Variables exported.
	without value. Needs to be able to export multiple variables at once. */

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

/* adds variable if there is an '='*/
int	add_var(char *var_name, t_data *data)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (ft_strchr(var_name, '=') == NULL)
		return (0);
	new_envp = (char **)malloc((count_env(data->envp) + 2) * sizeof(char *));
	if (!new_envp)
		return (-1);
	while (data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]); // need to handle strdup fail
		i++;
	}
	new_envp[i] = ft_strdup(var_name);
	new_envp[i + 1] = NULL;
	free_envp(data);
	data->envp = new_envp;
	return (0);
}

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
/* checks, if the variable already exists in env. If yes,
	it returns the index. if not it returns -1 */

bool	does_var_exist(char *var_name, char **envp)
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
			return (true);
		i++;
	}
	return (false);
}

/* variable name can only start with a-z, A-Z or '_' and can only contain a-z,
	A-Z, 0-9 and '_'
	valid variable name must be followd by '='   */

bool	is_valid_name(char *var_name, t_data *data)
{
	int	i;

	i = 1;
	if (!ft_isalpha(var_name[0]) && !var_name[0] != '_')
	{
		return (false);
	}
	while (1)
	{
		if (!ft_isalpha(var_name[i]) && !ft_isdigit(var_name[i])
			&& var_name[i] != '_' && var_name[i] != '=' && var_name[i] != '\0')
		{
			return (false);
		}
		if (var_name[i] == '\0')
			return (true);
		// if(var_name[i] == '=')
		// 	return(true);
		i++;
	}
	return (false);
}

void	update_var(char *var_name, t_data *data)
{
	int	i;

	i = 0;
	i = var_index(var_name, data->envp);
	free(data->envp[i]);
	data->envp[i] = ft_strdup(var_name);
}

/* example for command: command[0] = "export", command[1] = 'VAR_NAME=value'
	returns 0 on success, 1 on failure			*/

bool	builtin_export(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[0], "export") == 0 && args[1] == NULL) // just prints env
		return (print_export(data->envp));
	while (args[i])
	{
		if (!is_valid_name(args[i], data))
		{
			printf("bash: export: '%s': not a valid identifier\n", args[i]);
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

void	exec_int_function(t_data *data)
{
	if (strcmp(data->cmd->args[0], "export") == 0)
	{
		if (builtin_export(data->cmd->args, data) == true)
			data->exit_code = 0;
		else
			data->exit_code = 1;
		return ;
	}
}

/*  main is only for testing the internal commands. when testing,
	the first word must always be the internal command. because if its not ,
	the builtin_exporte	function would not have been called in the first place */

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_data		data;
	t_command	cmd;

	data.envp = copy_environ(envp);
	data.cmd = &cmd;
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
		add_history(input);
		data.cmd->args = ft_split(input, ' ');
		exec_int_function(&data);
		free_data_args(&data);
		free(input);
	}
	print_export(data.envp);
	clear_history();
	free_envp(&data);
	return (0);
}
