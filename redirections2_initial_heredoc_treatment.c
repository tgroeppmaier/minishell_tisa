/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2_initial_heredoc_treatment.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 22:55:48 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 11:54:15 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* returns -1 for error, 0 for success */
/* should be called only once, from the head of the tree*/
int	redirect_all_heredocs_to_pipes(t_tree *tree)
{
	int	res;

	if (0 != create_and_open_pipes_for_heredocs(tree))
		return (-1);
	if (0 == tree->head->heredoc_cnt)
		return (0);
	res = redirect_heredocs_to_pipes_recursively(tree);
	return (res);
}

/* returns -1 for error, 0 for success */
/* *index is the number of the heredoc we are treating now.
Should originally be called with &index, where int index == 0 */
/* Now we save this number in is_tkn_special, no need for index anymore */
int	redirect_heredocs_to_pipes_recursively(t_tree *tree)
{
	if (NULL == tree)
		return (0);
	redirect_heredocs_to_pipes_recursively(tree->left_child);
	if (EXEC == tree->node && NULL != tree->list)
	{
		redirect_heredocs_to_pipes(tree);
	}
	redirect_heredocs_to_pipes_recursively(tree->right_child);
	return (0);
}

/* Global version, 8 Dec 2023 */
/* Here is pretreating of heredocs, so no removal from the list */
int	redirect_heredocs_to_pipes(t_tree *tree)
{
	t_list	*ptr;
	int		res;

	if (NULL == tree || EXEC != tree->node || NULL == tree->list)
		return (print_error(1, "wrong call to redir heredoc"));
	ptr = tree->list;
	while (ptr)
	{
		if (ptr->is_special_tkn && ptr->next && !ft_strncmp(ptr->word, "<<", 3))
		{
			remove_outer_quotes(&ptr->next->word);
			res = do_redir_inin_part1_write_to_pipe(ptr->next->word, \
							ptr->is_special_tkn - 1, tree);
			if (res)
				return (res);
			ptr = ptr->next->next;
		}
		else
			ptr = ptr->next;
	}
	return (0);
}

int	do_redir_inin_part1_write_to_pipe(char const *endword, int pipe_num, \
								t_tree *tree)
{
	if (!tree)
		return (print_error(-1, "NULL in do_redir_inin"));
	if (pipe_num >= tree->head->heredoc_cnt)
		return (print_error(-2, "num of pipe is too big"));
	while (1)
		if (0 >= do_in_loop_heredoc(endword, \
				tree->head->heredoc_pipes[pipe_num][1]))
			break ;
	if (-1 == close(tree->head->heredoc_pipes[pipe_num][1]))
		print_error(1, "error closing writing end of heredoc pipe");
	return (0);
}

/* negative for error, 0 for exit from heredoc, 1 for continuing */
/* does not matter if we write "heredoc" welcome string to stdout or stderr,
because other redirections have not yet been performed? */
int	do_in_loop_heredoc(char const *endword, int pipe_fd_out)
{
	char	*curr_line;

	curr_line = NULL;
	if (1 == READLINE_MODE)
		curr_line = readline("heredoc > ");
	else if (0 == READLINE_MODE)
	{
		ft_printf_fd(2, "heredoc > ", getpid(), getppid());
		curr_line = get_next_line(STDIN_FILENO);
	}
	else
		return (print_error(-2, "Nothing else is possible in do_in_loop"));
	if (NULL == curr_line)
		return (print_error(-1, "NULL curr_line in do_in_loop. Ctrl+d mptst?"));
	if (0 == ft_strncmp(curr_line, endword, ft_strlen(endword)) && \
			ft_strlen(curr_line) + READLINE_MODE == ft_strlen(endword) + 1)
		do_free_str(&curr_line);
	else
	{
		if (-1 == write(pipe_fd_out, curr_line, ft_strlen(curr_line)))
			print_error(-3, "write problem: do in loop");
		do_free_str(&curr_line);
		return (1);
	}
	return (0);
}
