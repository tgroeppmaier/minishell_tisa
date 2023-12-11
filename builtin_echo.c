/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 04:14:07 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/07 22:59:48 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to check, if the -n option is set with echo
	(no trailing newline after echo print) */
// checks for special case, where word is "-"
// This is an old version. Timo has a new version. 7Dec2023 21:48
/* BUGS: echo "" leads to Invalid read of size 1.
	But only upon first call. The second call work fine.
	echo"" works as expected
*/
/*static bool	check_n(char *word)
{
	int	i;

	if (NULL == word)
	{
		print_error(1, "NULL in check_n");
		return (false);
	}
	i = 1;
	if (word[0] == '-')
	{
		while (word[i])
		{
			if (word[i] != 'n')
				return (false);
			i++;
		}
	}
	if (word[1] != 'n')
		return (false);
	else
		return (true);
}*/

// Timo new verion 7Dec 21:54
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

/* it does not check if words[0] == NULL because,
	when this function gets called, words[0] should be echo.
 words should be the command line, separated into words */

/*int	builtin_echo(t_tree *tree)
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
	while (node && true == check_n(node->word))
	{
		node = node->next;
	}
	while (node)
	{
		ft_printf_fd(STDOUT_FILENO, node->word);
		node = node->next;
		if (node)
			write(1, " ", 1);
	}
	if (tree->list->next && false == check_n(tree->list->next->word))
		write(1, "\n", 1);
	return (0);
}*/

// Timo new verion 7Dec 21:54
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
