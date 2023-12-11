/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 14:13:03 by aminakov         ###   ########.fr       */
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
		return (print_error(0, "empty string in ft_exec_exec"));
	if (!tree->list && \
			!is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (print_error(2, "NULL list in ft_exec_exec"));
	if (0 == tree->do_in_child_process)
		return (ft_exec_exec_no_new_process(tree));
	child = fork();
	if (-1 == child)
		return (print_error(3, "fork failed ft_exec_exec"));
	if (0 == child && restore_signals_in_children())
		do_in_child_exec_exit(tree);
	if (NULL == tree->data)
		print_error(4, "tree->data is NULL in ft_exec_exec");
	tree->data->exit_code = wait_for_all_return_chosen(child);
	return (tree->data->exit_code);
}

int	restore_signals_in_children(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (1);
}

int	do_in_child_exec_exit(t_tree *tree)
{
	char	**vector_cmd;
	int		res;

	if (NULL == tree)
		exit(print_error(1, "wrong call to do_in_child_exec_exit"));
	res = 0;
	if (0 == do_redirections(tree))
	{
		vector_cmd = get_vector_from_list(tree->list);
		res = ft_execute_cmd(vector_cmd, tree->data->envp);
		vector_cmd = NULL;
	}
	exit(do_clean_and_exit(res, tree));
}
/*		//free_split(vector_cmd);
no need: it got freed in ft_execute_cmd */

/* should we close all heredoc pipes here? */
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
