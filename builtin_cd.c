/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 04:55:40 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/02 11:55:32 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_value(t_data *data, char *var_name, char *value)
{
	int		i;
	char	*new;

	if (!data || !data->envp || !var_name || !value)
	{
		print_error(1, "NULL in set_env_value");
		return ;
	}
	new = ft_strjoin(var_name, value);
	if (NULL == new)
	{
		print_error(2, "failed ft_strjoin in set_env_value");
		return ;
	}
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

/*int	get_arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}*/

/* if PWD was unset before, what would happen? */
/*void	update_path(t_data *data)
{
	char	buffer[FILENAME_MAX];

	set_env_value(data, "OLDPWD=", ft_getenv("PWD", data));
	set_env_value(data, "PWD=", getcwd(buffer, sizeof(buffer)));
}*/

/*int	change_directory(t_data *data, const char *path)
{
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, \
		"bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	ft_printf_fd(2, "In change_directory\n\n");
	update_path(data);
	return (0);
}*/

static int	do_if_failed_cd(char const *path)
{
	ft_printf_fd(2, \
		"%s: cd: %s: No such file or directory\n", SHELL_NAME, path);
	return (1);
}

static void	do_update_var_free_str(char **ptr, t_data *data)
{
	update_var(*ptr, data);
	do_free_str(ptr);
}

// bash 0 for bash, bash 1 for zsh
int	change_directory(t_data *data, const char *path)
{
	char	curr_dir[FILENAME_MAX];
	char	*ptr;

	if (NULL == data || NULL == data->envp || NULL == path)
		return (print_error(1, "NULL in change_directory"));
	getcwd(curr_dir, sizeof(curr_dir));
	if (-1 == chdir(path))
		return (do_if_failed_cd(path));
	if (-1 != var_index("OLDPWD", data->envp))
	{
		ptr = ft_strjoin("OLDPWD=", curr_dir);
		do_update_var_free_str(&ptr, data);
	}
	else if (RESET_PWD_MODE)
		set_env_value(data, "OLDPWD=", curr_dir);
	if (-1 != var_index("PWD", data->envp))
	{
		getcwd(curr_dir, sizeof(curr_dir));
		ptr = ft_strjoin("PWD=", curr_dir);
		do_update_var_free_str(&ptr, data);
	}
	else if (RESET_PWD_MODE)
		set_env_value(data, "PWD=", curr_dir);
	return (0);
}

int	builtin_cd(t_tree *tree)
{
	char	*path;

	if (NULL == tree || NULL == tree->data || NULL == tree->list)
		return (print_error(1, "NULL in builtin_cd"));
	if (ft_lstsize(tree->list) > 2)
	{
		ft_printf_fd(2, "bash: cd: too many arguments\n");
		return (1);
	}
	if (NULL == tree->list->next || ft_strncmp(\
			tree->list->next->word, "~", 2) == 0)
	{
		path = ft_getenv("HOME", tree->data);
		if (NULL == path)
		{
			ft_printf_fd(2, "bash: cd: HOME not set\n");
			return (1);
		}
		return (change_directory(tree->data, path));
	}
	return (change_directory(tree->data, tree->list->next->word));
}
