/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:10:01 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/05 12:23:21 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char ***envp)
{
	int	i;

	if (NULL == envp || NULL == *envp)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		(*envp)[i] = NULL;
		i++;
	}
	free(*envp);
	*envp = NULL;
	return ;
}
// Set the original envp pointer to NULL

/* data and tree are two independent entities.
	They contain mutual pointers, but should be freed separately.
	In child processes before exit, data should be erased.
	In main show_prompt loop, only tree should be erased
		in the end of each iteration.
	Data should not be erased there, because it contains
		envp, working_dir, old_working_dir.
	In tree, envp is used to find path to a command written in PATH variable.
*/
void	free_data_except_tree(t_data *data)
{
	if (!data)
		return ;
	do_free_str(&data->working_dir);
	do_free_str(&data->old_working_dir);
	data->exit_code = 0;
	free_envp(&data->envp);
	ft_memset(data->builtins, '\0', sizeof(data->builtins));
	return ;
}

/*void	free_data_args(t_data *data)
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
}*/

/* frees the given variable,
	if it exists and shifts all following variables one spot forward in envp */

void	remove_var(t_data *data, char *var_name)
{
	int	i;

	if (NULL == data)
	{
		print_error(1, "NULL data in remove_var");
		return ;
	}
	if (NULL == var_name)
		print_error(2, "NULL var_name in remove_var");
	i = var_index(var_name, data->envp);
	if (i == -1)
		return ;
	free(data->envp[i]);
	while (data->envp[i])
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
	return ;
}

/* always returns 0 and does not print error message */

int	builtin_unset(t_tree *tree)
{
	t_list	*node;

	if (NULL == tree || NULL == tree->data)
		return (print_error(-1, "NULL tree or data in builtin_unset"));
	if (NULL == tree->list)
		return (print_error(-2, "NULL list in builtin_unset"));
	node = tree->list->next;
	if (NULL == node)
		return (0);
	while (node)
	{
		remove_var(tree->data, node->word);
		node = node->next;
	}
	return (0);
}
