#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

void	set_env_value(t_data *data, char *var_name, char *value)
{
	int		i;
	char	*new;

	new = ft_strjoin(var_name, value);
	i = var_index(var_name, data->envp);
	if (i == -1)
	{
		add_var(new, data);
		free(new);
	}
	else
	{
		free(data->envp[i]);
		data->envp[i] = new;
	}
}

int	get_arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	update_path(t_data *data)
{
	char	buffer[FILENAME_MAX];

	set_env_value(data, "OLDPWD=", ft_getenv("PWD", data));
	set_env_value(data, "PWD=", getcwd(buffer, sizeof(buffer)));
}

int	change_directory(t_data *data, const char *path)
{
	if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	update_path(data);
	return (0);
}

int	builtin_cd(t_data *data)
{
	char	*path;

	if (get_arg_count(data->cmd->args) > 2)
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	if (data->cmd->args[1] == NULL || ft_strcmp(data->cmd->args[1], "~") == 0)
	{
		path = ft_getenv("HOME", data);
		if (path == NULL)
		{
			printf("bash: cd: HOME not set\n");
			return (1);
		}
		return (change_directory(data, path));
	}
	return (change_directory(data, data->cmd->args[1]));
}
