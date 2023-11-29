/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:10:04 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 10:18:11 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_last_nl(char *str)
{
	int	len;

	if (NULL == str)
		return ;
	len = ft_strlen(str);
	if (0 == len)
		return ;
	if ('\n' == str[len - 1])
		str[len - 1] = '\0';
	return ;
}

int	show_prompt(char *envp[])
{
	char	*str;
	t_tree	*tree;
	int		bene;

	tree = NULL;
	bene = 1;
	while (bene++)
	{
		ft_printf("%s[%d]tisa%3d$ %s", GREEN, getpid(), bene - 1, WHITE);
		str = get_next_line(0);
		trim_last_nl(str);
		if (0 != parse_all(str) && 1 == do_free_str(&str))
			continue ;
		if (DEBUG_MODE)
			ft_printf("You entered [%s]\n", str);
		create_display_free_tree(&tree, str, 1 + 2 * DEBUG_MODE, envp);
		if (0 == ft_strncmp(str, "exit", ft_strlen(str) + 1))
			bene = 0;
		else
			ft_execute_tree(tree);
		free_tree(&tree);
		do_free_str(&str);
	}
	return (0);
}

int	do_free_str(char **str)
{
	if (NULL == str)
		return (0);
	free(*str);
	*str = NULL;
	return (1);
}
