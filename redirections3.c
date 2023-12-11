/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/10 09:58:19 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_redir_in_smaller(char const *file_in)
{
	int	fd;

	if (NULL == file_in)
		return (print_error(1, "NULL in do_redir_in_smaller"));
	if (-1 == access(file_in, F_OK))
		return (ft_error(2, "no such file", file_in));
	fd = open(file_in, O_RDONLY);
	if (-1 == fd)
		return (ft_error(3, "permission denied", file_in));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	do_redir_out_bigger(char const *file_out)
{
	int	fd;

	if (NULL == file_out)
		return (print_error(1, "NULL in do_redir_out_bigger"));
	fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == fd)
	{
		if (0 == access(file_out, F_OK))
			return (ft_error(2, "permission denied", file_out));
		return (ft_error(3, "cannot create file for writing", file_out));
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	do_redir_outout_biggerbigger(char const *file_out)
{
	int	fd;

	if (NULL == file_out)
		return (print_error(1, "NULL in do_redir_out_bigger"));
	fd = open(file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (-1 == fd)
	{
		if (0 == access(file_out, F_OK))
			return (ft_error(2, "permission denied", file_out));
		return (ft_error(3, "cannot create file for writing", file_out));
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	do_redir_inin_part2_read_from_pipe(int pipe_num, t_tree *tree)
{
	if (!tree)
		return (print_error(-1, "NULL in do_redir_inin2"));
	if (pipe_num >= tree->head->heredoc_cnt)
		return (print_error(-2, "num of pipe is too big"));
	if (pipe_num < 0)
		return (print_error(-3, "num of pipe is too little"));
	dup2(tree->head->heredoc_pipes[pipe_num][0], STDIN_FILENO);
	if (-1 == close(tree->head->heredoc_pipes[pipe_num][0]))
		print_error(1, "error closing reading end of heredoc pipe");
	return (0);
}
