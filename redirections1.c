/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 14:57:29 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_redir_in_smaller(char const *file_in, int last_heredoc)
{
	int	fd;

	if (NULL == file_in)
		return (print_error(1, "NULL in do_redir_in_smaller"));
	if (-1 == access(file_in, F_OK))
		return (ft_error(2, "no such file", file_in));
	fd = open(file_in, O_RDONLY);
	if (-1 == fd)
		return (ft_error(3, "permission denied", file_in));
	if (0 == last_heredoc)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
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

/* mystery here: moving free the tree to the beginning of child process
causes valgrind error */
/* No mystery: endword is a part of tree when you call for the function */
/* In the end, endword will be freed from inside this function,
even though it has const qualifier */
int	do_redir_inin_smallersmaller(char const *endword, t_tree *tree)
{
	int		pipe_fd[2];
	int		child;

	if (-1 == pipe(pipe_fd))
		return (print_error(1, "pipe problem heredoc"));
	child = fork();
	if (-1 == child)
		return (close_pipes_return(pipe_fd, 2, "fork problem heredoc"));
	if (0 == child)
	{
		signal(SIGQUIT, SIG_DFL);
		// signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		while (1)
			do_in_loop_heredoc_exit(tree, endword, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	waitpid(-1, NULL, 0);
	return (0);
}

int	do_in_loop_heredoc_exit(t_tree *tree, char const *endword, int pipe_fd_out)
{
	char	*curr_line;

	ft_printf("heredoc > ");
	curr_line = get_next_line(STDIN_FILENO);
	if (0 == ft_strncmp(curr_line, endword, ft_strlen(endword)) && \
			ft_strlen(curr_line) == ft_strlen(endword) + 1)
	{
		do_free_str(&curr_line);
		do_clean_and_exit(0, tree);
	}
	else
	{
		write(pipe_fd_out, curr_line, ft_strlen(curr_line));
		do_free_str(&curr_line);
	}
	return (1);
}
/*		free_data_except_tree(tree->data);
		do_free_str(&tree->cmd);
		tree_ptr = tree->head;
		free_tree(&tree_ptr);
		exit(0);*/
