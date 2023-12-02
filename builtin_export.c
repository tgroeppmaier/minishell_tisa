/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:48:57 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/02 11:22:35 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* adds variable if there is an '=' after var_name */

int	add_var(char *var_name, t_data *data)
{
	int		i;
	char	**new_envp;

	data->exit_code = 1;
	if (!data || !data->envp || !var_name)
		return (print_error(1, "add_var: not expected like this"));
	i = count_env(data->envp);
	if (ft_strchr(var_name, '=') == NULL)
		return (print_error(2, "no = in add_var"));
	new_envp = copy_environ(data->envp, 1);
	if (!new_envp)
		return (print_error(3, "failed copy_environ in add_var"));
	new_envp[i] = ft_strdup(var_name);
	if (!new_envp[i])
	{
		free_envp(&new_envp);
		return (print_error(4, "failed strdup in add_var"));
	}
	new_envp[i + 1] = NULL;
	free_envp(&(data->envp));
	data->envp = new_envp;
	data->exit_code = 0;
	return (0);
}

/*  returns index of given env variable, or -1 if its not found in env.
	can take varname or varname=value */
// What if var_name == "=tra-ta-ta"?
int	var_index(char *var_name, char **envp)
{
	int	i;
	int	len;

	if (NULL == var_name || NULL == envp)
		return (print_error(-1, "NULL input in var_index"));
	i = 0;
	len = 0;
	while (var_name[len])
	{
		if (var_name[len] == '=')
			break ;
		len++;
	}
	if (0 == len)
		return (print_error(-1, "name starts with = in var_index"));
	while (envp[i])
	{
		if ((0 == ft_strncmp(var_name, envp[i], len)) && \
						envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/* variable name can only start with a-z, A-Z or '_' and can only contain a-z,
	A-Z, 0-9 and '_'  */
/* the var_name should contain '=' */
bool	is_valid_name(char *var_name)
{
	int	i;

	if (NULL == var_name)
	{
		print_error(1, "No, NULL is not a proper name");
		return (false);
	}
	i = 1;
	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
		return (false);
	while (var_name[i])
	{
		if ('=' == var_name[i])
			return (true);
		if (!ft_isalpha(var_name[i]) && !ft_isdigit(var_name[i])
			&& var_name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/* takes variable + value and updates env */

int	update_var(char *var_name, t_data *data)
{
	int	i;

	if (NULL == data || NULL == var_name)
		return (print_error(1, "NULL in update_var"));
	i = var_index(var_name, data->envp);
	if (-1 == i)
	{
		ft_printf("since var_name is [%s]\n\n", var_name);
		return (print_error(2, "i is -1 in update_var"));
	}
	free(data->envp[i]);
	data->envp[i] = ft_strdup(var_name);
	if (0 == data->envp[i])
	{
		free(data->envp[i]);
		while (data->envp[i + 1])
			data->envp[i] = data->envp[i + 1];
		data->exit_code = 1;
		return (print_error(3, "failed strdup in update_var"));
	}
	data->exit_code = 0;
	return (0);
}

/* example for command: command[0] = "export", command[1] = 'VAR_NAME=value' */
// just prints env
// means, it is not yet in env
int	builtin_export(t_tree *tree)
{
	t_list	*node;

	if (NULL == tree || tree->data == NULL)
		return (print_error(1, "NULL in builtin_export"));
	if (EXEC != tree->node || NULL == tree->list)
		return (print_error(3, "not EXEC node or NULL list in builtin_export"));
	if (ft_strncmp(tree->list->word, "export", ft_strlen("export") + 1) == 0
		&& tree->list->next == NULL)
		return (print_env(tree->data->envp));
	node = tree->list->next;
	while (node)
	{
		if (!is_valid_name(node->word))
		{
			ft_printf_fd(2, "bash: export: '%s': not a valid identifier\n",
				node->word);
			return (1);
		}
		if (-1 == var_index(node->word, tree->data->envp))
			add_var(node->word, tree->data);
		else
			update_var(node->word, tree->data);
		node = node->next;
	}
	return (0);
}
