/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:10:59 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/05 13:43:05 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_data(t_data *data, char **envp)
{
	if (NULL == data)
		return (print_error(1, "set_data wrong input"));
	data->working_dir = NULL;
	data->old_working_dir = NULL;
	data->exit_code = 0;
	data->envp = copy_environ(envp, 0);
	if (NULL != envp && NULL == data->envp)
		return (print_error(2, "failed copy_environ in set_data"));
	ft_strlcpy(data->builtins, \
		"exit export env echo pwd cd unset", sizeof(data->builtins));
	return (0);
}
//		"exit export env echo pwd cd unset", sizeof(data->builtins));

/*	functions to change, or get data from the environment variables.
	We replace the env at the start of minishell with dynamically allocated
	memory to change and free it later without issues. */

int	print_env(char **envp)
{
	int	i;

	if (NULL == envp)
		return (print_error(-1, "Seriously? print NULL envp?"));
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	count_env(char **envp)
{
	int	i;

	if (NULL == envp)
		return (print_error(-1, "count_env: NULL input"));
	i = 0;
	while (envp[i] != NULL)
	{
		i++;
	}
	return (i);
}

/* dynamically allocates memory,
	copies the given env into it and returns pointer to it */

char	**copy_environ(char **envp, int additional_space)
{
	int		i;
	int		total_space;
	char	**new_envp;

	if (NULL == envp)
		return (NULL);
	total_space = count_env(envp) + additional_space + 1;
	new_envp = (char **)malloc(total_space * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			free_envp(&new_envp);
			print_error(1, "In copy_environ: not successful");
			return (NULL);
		}
	}
	while (i < total_space)
		new_envp[i++] = NULL;
	return (new_envp);
}

/* 	prints all environment variables to stdout.
	maybe use ft_putstr_fd?
	but if we redirect before calling it should not be necessary */

/* calling env to a existing directory ending with '/'
should give Permission denied.
For an existing file, should give Not a directory */
int	builtin_env(t_tree *tree)
{
	if (NULL == tree)
		return (print_error(1, "NULL tree in builtin_env"));
	if (NULL == tree->list)
		return (print_error(2, "NULL list in builtin_env"));
	if (tree->list->next == NULL)
	{
		print_env(tree->data->envp);
		return (0);
	}
	ft_printf_fd(2, "env: '%s': No such file or directory\n", \
		tree->list->next->word);
	return (127);
}
