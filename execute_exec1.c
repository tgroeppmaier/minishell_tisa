/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/10 22:04:59 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_tree	*tree_ptr;
int	ft_exec_exec(t_tree *tree)
{
	int		child;

	if (NULL == tree || EXEC != tree->node)
		return (print_error(1, "tr0|ft_exec_exec with not EXEC node"));
	if (!tree->list && is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (print_error(0, ""));
	if (!tree->list && \
			!is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (print_error(2, "NULL list in ft_exec_exec"));
	if (0 == tree->do_in_child_process)
		return (ft_exec_exec_no_new_process(tree));
	child = fork();
	if (-1 == child)
		return (print_error(3, "fork failed ft_exec_exec"));
	if (0 == child)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		do_in_child_exec_exit(tree);
	}
	return (wait_for_all_return_chosen(child));
}

int	do_in_child_exec_exit(t_tree *tree)
{
	char	*cmd;
	int		res;

	if (NULL == tree)
		exit (print_error(1, "wrong call to do_in_child_exec_exit"));
	res = 0;
	if (0 == do_redirections(tree))
	{
		cmd = get_cmd_from_list(tree->list);
		res = ft_execute_cmd(cmd, tree->data->envp);
		do_free_str(&cmd);
	}
	exit(do_clean_and_exit(res, tree));
}
/*	do_free_str(&tree->cmd);
	free_data_except_tree(tree->data);
	tree_ptr = tree->head;
	free_tree(&tree_ptr);
	exit(res);
*/

int	do_clean_and_exit(int res, t_tree *tree)
{
	t_tree	*tree_ptr;

	if (NULL == tree)
		return (print_error(-1, "NULL in do_clean_and_exit"));
	do_free_str(&tree->cmd);
	free_data_except_tree(tree->data);
	tree_ptr = tree->head;
	free_tree(&tree_ptr);
	exit(res);
}
