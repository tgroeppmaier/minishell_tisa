/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:04:34 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/13 11:47:45 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_tree(t_tree *tree)
{
	int	res;

	if (NULL == tree)
		return (0);
	if (0 == tree->bene)
		return (1);
	res = 0;
	if (PIPE == tree->node)
		res = ft_exec_pipe(tree);
	else if (EXEC == tree->node)
	{
		check_if_builtin_set_no_child_process(tree);
		res = ft_exec_exec(tree);
	}
	else if (SEMICOLON == tree->node)
		res = ft_exec_semicolon(tree);
	else if (ANDAND == tree->node)
		res = ft_exec_andand(tree);
	else if (OROR == tree->node)
		res = ft_exec_oror(tree);
	else if (BRACKETS == tree->node)
		res = ft_exec_brackets(tree);
	return (res);
}

/* Should be called only once, in show_prompt / show_prompt_readline */
int	treat_heredocs_execute_tree(t_tree *tree)
{
	if (NULL == tree)
		return (0);
	if (0 == tree->bene)
		return (1);
	redirect_all_heredocs_to_pipes(tree);
	expand_variables_all_tree(tree);
	expand_quotes_all_tree(tree);
	return (ft_execute_tree(tree));
}

/* we set tree->head->gpid to the pid of the first created child.
all newly created children have their gpid equal to the pid of 
that first child */
int	do_fork_set_gpid(t_tree *tree)
{
	int	child;

	if (NULL == tree)
		return (print_error(-1, "wrong call to do_fork"));
	child = fork();
	if (-1 == child)
		return (child);
	if (0 == child)
	{
		if (GPID_MODE)
		{
			if (-1 == tree->head->gpid)
			{
				tree->head->gpid = getpid();
			}
			setpgid(getpid(), tree->head->gpid);
		}
	}
	return (child);
}

/* should we close all heredoc pipes here? */
/* in the end, this is done in free_tree */
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
