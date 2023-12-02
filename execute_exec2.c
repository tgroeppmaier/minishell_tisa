/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/02 02:23:54 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//do_free_str(&tree->cmd);
//tree_ptr = tree->head;
//free_tree(&tree_ptr);

int	ft_exec_exec_no_new_process(t_tree *tree)
{
	char	*cmd;
	int		res;

	if (NULL == tree || EXEC != tree->node)
		return (print_error(1, "tr0|ft_exec_exec_no with not EXEC node"));
	if (NULL == tree->list)
		return (print_error(2, "NULL list in ft_exec_exec_no"));
	if (0 != tree->do_in_child_process)
		return (print_error(3, "wrong call to exec_no_new_process"));
	res = 0;
	if (0 == do_redirections(tree))
	{
		cmd = get_cmd_from_list(tree->list);
		res = ft_execute_cmd(cmd, tree->data->envp);
		do_free_str(&cmd);
	}
	return (res);
}

char	*ft_create_address(char const *dir, char const *file)
{
	char	*path_tmp;
	char	*path;

	if (NULL == dir || NULL == file)
		return (NULL);
	path_tmp = ft_strjoin(dir, "/");
	path = ft_strjoin(path_tmp, file);
	ft_clear_path(&path_tmp);
	return (path);
}

char	*get_path_for_cmd(char *cmd, char *envp[])
{
	int		i;
	char	**paths;
	char	*path;

	if (NULL == cmd)
		return (ft_err_clear_ptr(NULL, NULL, "Bad address", cmd));
	i = 0;
	while (NULL != envp[i] && NULL == ft_strnstr(envp[i], "PATH", 4))
		++i;
	if (NULL == envp[i])
		return (ft_err_clear_ptr(NULL, NULL, "no PATH variable", NULL));
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (NULL != paths[++i])
	{
		path = ft_create_address(paths[i], cmd);
		if (NULL == path)
			return (ft_err_clear_ptr(0, paths, "problem creating path", 0));
		if (0 == access(path, X_OK))
			return (ft_err_clear_ptr(path, paths, NULL, NULL));
		ft_clear_path(&path);
	}
	return (ft_err_clear_ptr(NULL, paths, "command not found", cmd));
}

// before realizing also the paths, so not only taking from PATH variable
int	ft_execute_cmd_path(char *cmd, char *envp[])
{
	char	*path;
	char	**cmd_vector;

	cmd_vector = ft_split(cmd, ' ');
	path = get_path_for_cmd(cmd_vector[0], envp);
	if (!path)
	{
		free_split(cmd_vector);
		return (1);
	}
	execve(path, cmd_vector, envp);
	ft_clear_path(&path);
	free_split(cmd_vector);
	return (0);
}

/*if (NULL == cmd)
		return (print_error(1, "NULL in ft_execute_cmd"));
It is not a mistake, it happens if there are redirections
without a command. */
int	ft_execute_cmd(char *cmd, char *envp[])
{
	char	*path;
	char	**cmd_vector;
	char	*ptr_last_slash;
	int		pos;

	if (NULL == cmd)
		return (print_error(0, ""));
	pos = find_setsymb(cmd, " /", cr_sgm(0, ft_strlen(cmd)));
	if (-1 == pos || ' ' == cmd[pos])
		return (ft_execute_cmd_path(cmd, envp));
	cmd_vector = ft_split(cmd, ' ');
	ptr_last_slash = ft_strrchr(cmd_vector[0], '/');
	path = cmd_vector[0];
	cmd_vector[0] = ptr_last_slash + 1;
	if (0 != access(path, F_OK))
		return (redef_clear_in_exec(1, cmd_vector, path, "command not found"));
	else if (0 == access(path, F_OK) && 0 != access(path, X_OK))
		return (redef_clear_in_exec(2, cmd_vector, path, "permission denied"));
	execve(path, cmd_vector, envp);
	cmd_vector[0] = path;
	ft_err_clear_ptr(NULL, cmd_vector, path, "is a directory");
	return (0);
}
