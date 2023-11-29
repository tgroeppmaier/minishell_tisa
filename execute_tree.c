/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:04:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 10:22:34 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_tree(t_tree *tree)
{
	if (NULL == tree)
		return (0);
	if (0 == tree->bene)
		return (1);
	if (DEBUG_MODE)
		ft_printf_fd(STDERR_FILENO, "Now the tree will be executed!\n");
	if (PIPE == tree->node)
		ft_exec_pipe(tree);
	else if (EXEC == tree->node)
		ft_exec_exec(tree);
	return (0);
}

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
int	ft_exec_pipe(t_tree *tree)
{
	int	pipe_fd[2];
	int	child1;
	int	child2;

	if (DEBUG_MODE)
		ft_printf_fd(STDERR_FILENO, "Ok, we will treat pipe!\n");
	if (NULL == tree || PIPE != tree->node)
		return (print_error(1, "wrong call to ft_exec_pipe"));
	if (-1 == pipe(pipe_fd))
		return (print_error(2, "problem opening pipe"));
	child1 = fork();
	if (-1 == child1)
		return (close_pipes_return(pipe_fd, 3, "problem with fork1"));
	if (0 == child1)
		return (ft_dopipe_in_childleft(tree->left_child, pipe_fd));
	child2 = fork();
	if (-1 == child2)
		return (print_error(4, "problem with fork2"));
	if (0 == child2)
		return (ft_dopipe_in_childright(tree->right_child, pipe_fd));
	close_pipes_return(pipe_fd, 0, NULL);
	while ((-1 != waitpid(-1, NULL, 0) || ECHILD != errno))
		if (DEBUG_MODE)
			ft_printf_fd(2, "child finished execution\n");
	return (0);
}

int	close_pipes_return(int pipe_fd[2], int res, char const *msg)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (res && msg)
		return (print_error(res, msg));
	return (res);
}

int	ft_dopipe_in_childleft(t_tree *tree, int pipe_fd[2])
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
	exit(res);
	return (res);
}

int	ft_dopipe_in_childright(t_tree *tree, int pipe_fd[2])
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
	exit(res);
	return (res);
}
