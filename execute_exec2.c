/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 21:34:20 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_exec_no_new_process(t_tree *tree)
{
	char	**vector_cmd;
	int		res;
	t_sgm	fds_copy;

	if (NULL == tree || EXEC != tree->node)
		return (print_error(1, "tr0|ft_exec_exec_no with not EXEC node"));
	if (NULL == tree->list)
		return (print_error(2, "NULL list in ft_exec_exec_no"));
	if (0 != tree->do_in_child_process)
		return (print_error(3, "wrong call to exec_no_new_process"));
	make_a_copy_of_fd(&fds_copy, tree);
	res = do_redirections(tree);
	if (0 == res)
	{
		res = exec_int_function(tree);
		if (-1 == res)
		{
			vector_cmd = get_vector_from_list(tree->list);
			res = ft_execute_cmd(vector_cmd, tree->data->envp);
			vector_cmd = NULL;
		}
	}
	tree->data->exit_code = res;
	restore_file_descriptors_close_copies(fds_copy, tree);
	return (res);
}
/* free_split(vector_cmd);
 no need-it got freed as soon as possible in ft_execute_cmd*/

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
	{
		return (ft_err_clear_ptr(NULL, NULL, "Bad address", cmd));
	}
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
	return (ft_err_clear_ptr(NULL, paths, "Command not found", cmd));
}

// before realizing also the paths, so not only taking from PATH variable
/* 9Dec2023: it is a bad practice. For instance, 
"  '' sdf " would result in cmd '' not found,
 instead of cmd  '' sdf not found.
Instead, do this directly from list, without merging it to one string. */
/*if DEBUG_MODE causes SIGPIPE for cat <<xxx|cat<<yyy, not clear why.
It is like ft_printf to a writing part of the pipe, while all reading ends
were already close. But why cat<<xxx|cat does not trigger this? */
int	ft_execute_cmd_path(char **vector_cmd, char *envp[])
{
	char	*path;

	path = get_path_for_cmd(vector_cmd[0], envp);
	if (!path)
	{
		if (DEBUG_MODE)
			ft_printf_fd(2, "path did not work. cmd is [%s]\n", vector_cmd[0]);
		free_split(vector_cmd);
		return (127);
	}
	execve(path, vector_cmd, envp);
	ft_clear_path(&path);
	free_split(vector_cmd);
	return (0);
}

/* if there is '/' in the list->word, in case of failure it will write
bash: list->word: No such file or directory
if there is no '/', it will write
Command 'list->word' not found, did you mean... in case it wants 
to suggest something, or
list->word: command not found */
/*if (NULL == cmd_vector[0])
		return (print_error(0, "NULL cmd_vector[0] in ft_execute_cmd"));
It is not a mistake, it happens if there are redirections
without a command. */
int	ft_execute_cmd(char **vector_cmd, char *envp[])
{
	char	*path;
	char	*ptr_last_slash;
	int		pos;

	if (NULL == vector_cmd)
		return (print_error(0, "NULL vector_cmd in ft_execute_cmd"));
	if (NULL == vector_cmd[0])
		return (print_error(1, "NULL vector_cmd[0] in ft_execute_cmd"));
	pos = find_setsymb(vector_cmd[0], "/", cr_sgm(0, ft_strlen(vector_cmd[0])));
	if (-1 == pos)
		return (ft_execute_cmd_path(vector_cmd, envp));
	ptr_last_slash = ft_strrchr(vector_cmd[0], '/');
	path = vector_cmd[0];
	vector_cmd[0] = ptr_last_slash + 1;
	if (0 != access(path, F_OK))
		return (redef_clear_in_exec(2, vector_cmd, path, \
					"No such file or directory"));
	else if (0 == access(path, F_OK) && 0 != access(path, X_OK))
		return (redef_clear_in_exec(126, vector_cmd, path, "permission denied"));
	execve(path, vector_cmd, envp);
	vector_cmd[0] = path;
	ft_err_clear_ptr(NULL, vector_cmd, path, "is a directory");
	return (0);
}

/*if (NULL == cmd)
		return (print_error(1, "NULL in ft_execute_cmd"));
It is not a mistake, it happens if there are redirections
without a command. */
/*old version. The new one works on list.
int	ft_execute_cmd(char *cmd, char *envp[])
{
	char	*path;
	char	**cmd_vector;
	char	*ptr_last_slash;
	int		pos;

	if (NULL == cmd)
		return (print_error(0, "NULL cmd in ft_execute_cmd"));
	if (is_str_empty(cmd, cr_sgm(0, ft_strlen(cmd))))
	{
		ft_printf_fd(2, "string is empty");
		return (print_err_empty_str_in_cmd(127, cmd));
	}
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
}*/
