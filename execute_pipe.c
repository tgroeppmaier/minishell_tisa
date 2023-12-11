/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:04:34 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 14:25:53 by aminakov         ###   ########.fr       */
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
	{
		return (close_pipes_return(pipe_fd, 3, "problem with fork1"));
	}
	if (0 == child1)
		return (ft_dopipe_in_childleft_exit(tree->left_child, pipe_fd));
	child2 = fork();
	if (-1 == child2)
		return (print_error(4, "problem with fork2"));
	if (0 == child2)
		return (ft_dopipe_in_childright_exit(tree->right_child, pipe_fd));
	close_pipes_return(pipe_fd, 0, NULL);
	if (NULL == tree->data)
		print_error(5, "NULL tree->data in ft_exec_pipe");
	tree->data->exit_code = wait_for_all_return_chosen(child2);
	return (tree->data->exit_code);
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

	res = 53;
	while (1)
	{
		child = waitpid(-1, &wstatus, 0);
		if (-1 == child && ECHILD == errno)
			break ;
		if (child == childchosen)
			res = wstatus;
		if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGQUIT)
		{
			ft_printf_fd(2, "Quit (core dumped)\n");
			exit(3 + 128);
		}
	}
	if (DEBUG_MODE)
		ft_printf_fd(2, "in parent process res [%d]\n\n", res);
	if (WIFEXITED(res))
		return (WEXITSTATUS(res));
	return (res + 128);
}
/*		if (DEBUG_MODE)
			ft_printf_fd(2, \
		"child [%d] finished execution with [%d][%d][%d]\n\n", \
		child, wstatus, WIFEXITED(wstatus), WEXITSTATUS(wstatus));
*/

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

	signal(SIGINT, SIG_DFL);
	if (-1 == close(pipe_fd[0]))
		print_error(-1, "close in childleft failed");
	dup2(pipe_fd[1], STDOUT_FILENO);
	if (-1 == close(pipe_fd[1]))
		print_error(-2, "close2 in childleft failed");
	--tree->do_in_child_process;
	res = ft_execute_tree(tree);
	if (DEBUG_MODE)
		ft_printf_fd(2, "In child left are going to exit with [%d]\n", res);
	exit(do_clean_and_exit(res, tree));
}
/*	do_free_str(&tree->cmd);
	free_data_except_tree(tree->data);
	tree_ptr = tree->head;
	free_tree(&tree_ptr);
	exit(res); */

int	ft_dopipe_in_childright_exit(t_tree *tree, int pipe_fd[2])
{
	int		res;

	signal(SIGINT, SIG_DFL);
	if (-1 == close(pipe_fd[1]))
		print_error(-1, "r:close pipe_fd[1]");
	dup2(pipe_fd[0], STDIN_FILENO);
	if (-1 == close(pipe_fd[0]))
		print_error(-2, "r:close pipe_fd[0]");
	--tree->do_in_child_process;
	res = ft_execute_tree(tree);
	if (DEBUG_MODE)
		ft_printf_fd(2, "In child right are going to exit with [%d]\n", res);
	exit(do_clean_and_exit(res, tree));
}
/*	do_free_str(&tree->cmd);
	free_data_except_tree(tree->data);
	tree_ptr = tree->head;
	free_tree(&tree_ptr);
	exit(res);*/
