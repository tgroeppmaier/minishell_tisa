/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/10 18:12:28 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_err_clear_ptr(char *res, char **paths, char const *msg1, \
						char const *msg2)
{
	if (!msg1 || '\0' == *msg1)
	{
		free_split(paths);
		return (res);
	}
	ft_printf_fd(STDERR_FILENO, "%s%s", BUFF_RED, msg1);
	if (msg2 && *msg2)
		ft_printf_fd(STDERR_FILENO, ": [%s]", msg2);
	ft_printf_fd(STDERR_FILENO, "%s\n", RES);
	free_split(paths);
	return (res);
}

int	ft_error(int res, char const *msg1, char const *msg2)
{
	if (!msg1 || !*msg1)
		return (res);
	if (res)
		ft_printf_fd(STDERR_FILENO, RED);
	ft_printf_fd(STDERR_FILENO, "%s", msg1);
	if (NULL != msg2 && '\0' != *msg2)
		ft_printf_fd(STDERR_FILENO, ": [%s]", msg2);
	ft_printf_fd(STDERR_FILENO, "\n\n");
	if (res)
		ft_printf_fd(STDERR_FILENO, RES);
	return (res);
}

void	ft_clear_path(char **path)
{
	if (NULL == path || NULL == *path)
		return ;
	free(*path);
	*path = NULL;
	return ;
}

/* 10Dec2023: it is a bad design to use this function */
/*char	*get_cmd_from_list(t_list *list)
{
	t_list	*ptr;
	int		len;
	char	*res;

	len = 0;
	ptr = list;
	while (ptr)
	{
		len += ft_strlen(ptr->word) + 1;
		ptr = ptr->next;
	}
	if (len == 0)
		return (NULL);
	res = (char *)malloc(len);
	res[0] = '\0';
	ptr = list;
	while (ptr)
	{
		ft_strlcat(res, ptr->word, len);
		ptr = ptr->next;
		if (ptr)
			ft_strlcat(res, " ", len);
	}
	return (res);
}*/

char	**get_vector_from_list(t_list *list)
{
	int		list_len;
	char	**cmd_vector;
	int		index;

	if (NULL == list)
		return (NULL);
	list_len = ft_lstsize(list);
	cmd_vector = (char **)malloc((list_len + 1) * sizeof(char *));
	index = -1;
	while (++index < list_len)
	{
		cmd_vector[index] = ft_strdup(list->word);
		list = list->next;
	}
	cmd_vector[index] = NULL;
	if (DEBUG_MODE)
	{
		index = -1;
		ft_printf_fd(2, "\n\nvector_cmd:\n");
		while (cmd_vector[++index])
			ft_printf_fd(2, "--%s--", cmd_vector[index]);
		ft_printf_fd(2, "\n\n");
	}
	return (cmd_vector);
}

int	redef_clear_in_exec(int res, char **cmd_vector, char *path, char const *msg)
{
	cmd_vector[0] = path;
	ft_err_clear_ptr(NULL, cmd_vector, msg, path);
	return (res);
}
