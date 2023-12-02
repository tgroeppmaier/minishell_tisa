/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:49:36 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/02 05:30:27 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns -1 if the command is not builtin, to further pass it to execve.
	0 if it was a builtin command.
	But does a builtin command always return (0) unless it is a exit?
	(because in later case we do not care -- it will be a different process)
	For instane, it returns 1 for exit 123 asd, and stay in the same process.
 */

int	exec_int_function(t_tree *tree)
{
	if (NULL == tree)
		return (print_error(1, "NULL in exec_int_function"));
	if (EXEC != tree->node)
		return (print_error(2, "not EXEC node in exec_int_function"));
	if (NULL == tree->list && \
			1 != is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (print_error(3, "not expanded list in exec_int_function"));
	if (NULL == tree->list)
		return (4);
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
