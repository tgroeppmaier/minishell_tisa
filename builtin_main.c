/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:49:36 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/11 11:02:23 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns -1 if the command is not builtin, to further pass it to execve.
	0 if it was a builtin command.
	But does a builtin command always return (0) unless it is a exit?
	(because in later case we do not care -- it will be a different process)
	For instane, it returns 1 for exit 123 asd, and stay in the same process.
 */

/*
returns 0, if builtin
returns -1, if need to pass to execve
returns >0 if error (and so no need to pass to execve)
*/
/* if we got an empty list, this means there is nothing to do,
 no redirections etc*/
/* empty list in EXEC happens for instance for spaces as a command */
int	check_if_builtin_set_no_child_process(t_tree *tree)
{
	t_list	*ptr;

	if (!tree || EXEC != tree->node || !tree->data)
		return (print_error(1, "NULL or not EXEC in is_builtin"));
	if (!tree->list)
		return (print_error(0, "empty list in EXEC. It is not bad, right?"));
	ptr = tree->list;
	while (ptr)
	{
		if (ptr->is_special_tkn && ptr->next)
			ptr = ptr->next->next;
		else
			break ;
	}
	if (ptr)
	{
		if (is_str_one_of_setstr(ptr->word, tree->data->builtins))
		{
			tree->is_builtin = 1;
			tree->do_in_child_process = 0;
			return (0);
		}
	}
	return (-1);
}

int	exec_int_function(t_tree *tree)
{
	if (NULL == tree)
		return (print_error(1, "NULL in exec_int_function"));
	if (EXEC != tree->node)
		return (print_error(2, "not EXEC node in exec_int_function"));
	if (NULL == tree->list && \
			1 != is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (print_error(0, "NULL list in exec_int_function; redir?"));
	if (NULL == tree->list)
		return (print_error(3, "NULL tree->list with empty str exec_int"));
	if (0 == ft_strncmp(tree->list->word, "exit", ft_strlen("exit") + 1))
		return (builtin_exit(tree));
	if (0 == ft_strncmp(tree->list->word, "export", ft_strlen("export") + 1))
		return (builtin_export(tree));
	if (0 == ft_strncmp(tree->list->word, "env", ft_strlen("env") + 1))
		return (builtin_env(tree));
	if (0 == ft_strncmp(tree->list->word, "echo", ft_strlen("echo") + 1))
		return (builtin_echo(tree));
	if (0 == ft_strncmp(tree->list->word, "pwd", ft_strlen("pwd") + 1))
		return (builtin_pwd(tree));
	if (0 == ft_strncmp(tree->list->word, "cd", ft_strlen("cd") + 1))
		return (builtin_cd(tree));
	if (0 == ft_strncmp(tree->list->word, "unset", ft_strlen("unset") + 1))
		return (builtin_unset(tree));
	return (-1);
}
