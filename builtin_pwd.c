/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 04:38:45 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/02 09:49:08 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var_name, t_data *data)
{
	int		i;
	int		k;
	char	*value;

	if (!var_name || !data)
	{
		print_error(1, "NULL in ft_getenv");
		return (NULL);
	}
	k = 0;
	i = var_index(var_name, data->envp);
	if (-1 == i)
		return (NULL);
	while (data->envp[i][k])
	{
		if ('=' == data->envp[i][k])
			break ;
		k++;
	}
	value = data->envp[i] + k + 1;
	return (value);
}

// this should work even if PWD is not set. Even if PATH is not set
/*int	builtin_pwd(t_tree *tree)
{
	char	*pwd;

	pwd = ft_getenv("PWD", tree->data);
	if (pwd == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "PWD environment variable not set\n");
		return (1);
	}
	else
	{
		ft_printf_fd(STDOUT_FILENO, "%s\n", pwd);
		return (0);
	}
}*/

/*if (NULL == tree || NULL == tree->data || EXEC != tree->node)
	return (print_error(-1, "smth wrong in builtin_pwd"));*/
int	builtin_pwd(t_tree *tree)
{
	char	pwd[FILENAME_MAX];

	(void) tree;
	ft_strlcpy(pwd, getcwd(pwd, sizeof(pwd)), sizeof(pwd));
	ft_printf_fd(STDOUT_FILENO, "%s\n", pwd);
	return (0);
}
