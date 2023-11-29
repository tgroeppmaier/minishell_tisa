/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:04:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 17:32:34 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* everything is done inside a new child process.
bash and zsh work differently in that.
I guess we mimick bash in that*/
/*No. The difference betweeen zsh and bash is that
in zsh cmd1 | cmd2 only child process for cmd1 is created
in bash two child process are created: one for cmd1 and another for child2.
My problem with a child process propagating to next iteration of prompt loop
is not in that. But not clear where.*/
/* There were two problems: left_child written instead of right_child and 
free_tree(&(*tree)->head). Instead ptr = (*tree)->head; free_tree(&ptr);*/
/* Another problem, with child propagating to the next iterations,
must be solved with exit instead of return in child processes */
int	ft_exec_pipe(t_tree *tree)
{
	int	pipe_fd[2];
	int	child1;
	int	child2;

	if (NULL == tree || PIPE != tree->node)
		return (print_error(1, "wrong call to ft_exec_pipe"));
	if (-1 == pipe(pipe_fd))
		return (print_error(2, "problem opening pipe"));
	child1 = fork();
	if (-1 == child1)
		return (close_pipes_return(pipe_fd, 3, "problem with fork1"));
	if (0 == child1)
		return (ft_dopipe_in_childleft_exit(tree->left_child, pipe_fd));
	child2 = fork();
	if (-1 == child2)
		return (print_error(4, "problem with fork2"));
	if (0 == child2)
		return (ft_dopipe_in_childright_exit(tree->right_child, pipe_fd));
	close_pipes_return(pipe_fd, 0, NULL);
	return (wait_for_all_return_chosen(child2));
}
/* need to distinguish between the left and right process to finish,i
because need to return the result of the right one */
/*while ((-1 != waitpid(-1, &res, 0) || ECHILD != errno))
	if (DEBUG_MODE)
		ft_printf_fd(2, "child finished execution with [%d]\n\n", res);
return (res);*/

int	wait_for_all_return_chosen(int childchosen)
{
	int	child;
	int	wstatus;
	int	res;

	while (1)
	{
		child = waitpid(-1, &wstatus, 0);
		if (-1 != child || ECHILD != errno)
		{
			if (child == childchosen)
				res = wstatus;
			if (DEBUG_MODE)
				ft_printf_fd(2, \
					"child [%d] finished execution with [%d]\n\n", \
						child, wstatus);
		}
		else
			break ;
	}
	if (DEBUG_MODE)
		ft_printf_fd(2, "in parent process returning [%d]\n\n", res);
	return (res);
}

int	close_pipes_return(int pipe_fd[2], int res, char const *msg)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (res && msg)
		return (print_error(res, msg));
	return (res);
}

int	ft_dopipe_in_childleft_exit(t_tree *tree, int pipe_fd[2])
{
	int		res;
	t_tree	*tree_ptr;

	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	--tree->do_in_child_process;
	res = ft_execute_tree(tree);
	do_free_str(&tree->cmd);
	tree_ptr = tree->head;
	free_tree(&tree_ptr);
	if (DEBUG_MODE)
		ft_printf_fd(2, "In child left are going to exit with [%d]\n", res);
	exit(res);
}

int	ft_dopipe_in_childright_exit(t_tree *tree, int pipe_fd[2])
{
	int		res;
	t_tree	*tree_ptr;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	--tree->do_in_child_process;
	res = ft_execute_tree(tree);
	do_free_str(&tree->cmd);
	tree_ptr = tree->head;
	free_tree(&tree_ptr);
	if (DEBUG_MODE)
		ft_printf_fd(2, "In child right are going to exit with [%d]\n", res);
	exit(res);
}
