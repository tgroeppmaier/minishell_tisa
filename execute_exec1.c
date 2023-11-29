/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 14:31:07 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_tree	*tree_ptr;
int	ft_exec_exec(t_tree *tree)
{
	int		child;

	if (NULL == tree || EXEC != tree->node)
		return (print_error(1, "tr0|ft_exec_exec with not EXEC node"));
	if (!tree->list)
		return (print_error(2, "NULL list in ft_exec_exec"));
	if (0 == tree->do_in_child_process)
		return (ft_exec_exec_no_new_process(tree));
	child = fork();
	if (-1 == child)
		return (print_error(3, "fork failed ft_exec_exec"));
	if (0 == child)
	{
		do_in_child_exec_exit(tree);
	}
	waitpid(-1, NULL, 0);
	return (0);
}

int	do_in_child_exec_exit(t_tree *tree)
{
	char	*cmd;
	t_tree	*tree_ptr;

	if (NULL == tree)
		exit (print_error(1, "wrong call to do_in_child_exec_exit"));
	if (0 == do_redirections(tree))
	{
		cmd = get_cmd_from_list(tree->list);
		ft_execute_cmd(cmd, tree->envp);
		do_free_str(&cmd);
	}
	do_free_str(&tree->cmd);
	tree_ptr = tree->head;
	free_tree(&tree_ptr);
	exit(0);
}
