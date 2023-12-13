/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/13 12:56:51 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_tree	*tree_ptr;
/*int	ft_exec_exec(t_tree *tree)
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
	child = do_fork_set_gpid(tree);
	if (-1 == child)
		return (print_error(3, "fork failed ft_exec_exec"));
	if (0 == child && restore_signals_in_children())
		do_in_child_exec_exit(tree);
	if (NULL == tree->data)
		print_error(4, "tree->data is NULL in ft_exec_exec");
	tree->data->exit_code = wait_for_all_return_chosen(child);
	return (tree->data->exit_code);
}*/

int	set_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		return (print_error(5, "sigaction failed in crchsetsig"));
	return (0);
}

int	unset_signals(void)
{
	struct sigaction	old_sa;

	old_sa.sa_handler = handle_sigint;
	sigemptyset(&old_sa.sa_mask);
	old_sa.sa_flags = 0;
	if (sigaction(SIGINT, &old_sa, NULL) < 0)
		return (print_error(6, "sigaction failed in ft_exec_exec"));
	return (0);
}

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
	child = do_fork_set_gpid(tree);
	if (-1 == child)
		return (print_error(3, "fork failed ft_exec_exec"));
	if (0 == child && restore_signals_in_children())
		do_in_child_exec_exit(tree);
	set_signals();
	if (NULL == tree->data)
		print_error(4, "tree->data is NULL in waitchrestsig");
	tree->data->exit_code = wait_for_all_return_chosen(child);
	unset_signals();
	return (tree->data->exit_code);
}

/*int	create_child_and_setup_signals(t_tree *tree)
{
	int					child;
	struct sigaction	sa;

	if (NULL == tree || EXEC != tree->node)
		return (print_error(1, "tr0|ft_exec_exec with not EXEC node"));
	if (!tree->list && is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (print_error(0, "empty string in ft_exec_exec"));
	if (!tree->list && !is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (print_error(2, "NULL list in ft_exec_exec"));
	if (0 == tree->do_in_child_process)
		return (ft_exec_exec_no_new_process(tree));
	child = do_fork_set_gpid(tree);
	if (-1 == child)
		return (print_error(3, "fork failed ft_exec_exec"));
	if (0 == child && restore_signals_in_children())
		do_in_child_exec_exit(tree);
	else
	{
		sa.sa_handler = SIG_IGN;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return (print_error(5, "sigaction failed in crchsetsig"));
	}
	return (child);
}*/

/*int	wait_for_child_and_restore_signals(t_tree *tree, int child)
{
	struct sigaction	old_sa;
	int					res;

	if (NULL == tree->data)
		return (print_error(4, "tree->data is NULL in waitchrestsig"));
	res = wait_for_all_return_chosen(child);
	if (128 + 53 != res)
		tree->data->exit_code = res;
	old_sa.sa_handler = handle_sigint;
	sigemptyset(&old_sa.sa_mask);
	old_sa.sa_flags = 0;
	if (sigaction(SIGINT, &old_sa, NULL) < 0)
		return (print_error(6, "sigaction failed in ft_exec_exec"));
	return (tree->data->exit_code);
}*/

/*int	ft_exec_exec(t_tree *tree)
{
	int	child;

	child = create_child_and_setup_signals(tree);
	return (wait_for_child_and_restore_signals(tree, child));
}*/

int	restore_signals_in_children(void)
{
	if (0 == GPID_MODE)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
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
