/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 04:14:07 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/06 09:22:03 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to check, if the -n option is set with echo
	(no trailing newline after echo print)
	checks for special case, where word is "-" */

static bool	check_n(char *word)
{
	int	i;

	if (word == NULL || word[0] != '-' || word[1] == '\0')
		return (false);
	i = 1;
	while (word[i])
	{
		if (word[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/* skips over one or several valid -n flags example: -nnnnnnnn */

int	builtin_echo(t_tree *tree)
{
	t_list	*node;

	if (NULL == tree || NULL == tree->data || NULL == tree->list)
		return (print_error(1, "NULL in builtin_echo"));
	node = tree->list->next;
	if (NULL == node)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	while (node && check_n(node->word))
		node = node->next;
	while (node)
	{
		if (node->word && node->word[0] != '\0')
		{
			ft_putstr_fd(node->word, STDOUT_FILENO);
			if (node->next)
				write(STDOUT_FILENO, " ", 1);
		}
		node = node->next;
	}
	if (tree->list->next && !check_n(tree->list->next->word))
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
