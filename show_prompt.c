/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:10:04 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 13:38:54 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_last_nl(char *str)
{
	int	len;

	if (NULL == str)
	{
		ft_printf("You probably entered Ctrl+D on empty string\n");
		return ;
	}
	len = ft_strlen(str);
	if (0 == len)
		return ;
	if ('\n' == str[len - 1])
		str[len - 1] = '\0';
	else
		ft_printf("You probably entered Ctrl+D on non empty string\n");
	return ;
}

int	show_prompt(t_data *data)
{
	char	*str;
	t_tree	*tree;
	int		bene;

	tree = NULL;
	bene = 1;
	while (bene++)
	{
		ft_printf("%s[%d]%s%3d$ %s", OPTGREEN, getpid(), \
				SHELL_NAME, bene - 1, OPTWHITE);
		str = get_next_line(0);
		trim_last_nl(str);
		if (DEBUG_MODE)
			ft_printf("You entered [%s]\n", str);
		if (0 != parse_all(str) && 1 == do_free_str(&str))
			continue ;
		create_display_free_tree(&tree, str, 1 + 2 * DEBUG_MODE, data);
		if (0 == ft_strncmp(str, "exit", ft_strlen(str) + 1))
			bene = 0;
		else
			treat_heredocs_execute_tree(tree);
		free_tree(&tree);
		do_free_str(&str);
		ft_printf_fd(2, "\n\n        exit_code is [%d]\n", data->exit_code);
	}
	return (data->exit_code);
}

int	do_free_str(char **str)
{
	if (NULL == str)
		return (0);
	free(*str);
	*str = NULL;
	return (1);
}
