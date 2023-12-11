/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:23:12 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/11 13:14:39 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	calculate_buffer_size(const char *str)
{
	size_t	size;
	char	outer_quote;
	size_t	i;

	if (NULL == str)
		return (print_error(-1, "NULL in calculate_buffer_size"));
	size = 0;
	outer_quote = '\0';
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && outer_quote == '\0')
			outer_quote = str[i];
		else if (str[i] == outer_quote)
			outer_quote = '\0';
		else
			++size;
		++i;
	}
	return (size);
}

void	copy_without_quotes(char *dest, const char *src)
{
	size_t	dest_index;
	char	outer_quote;
	size_t	i;

	if (!src || !dest)
		print_error(1, "NULL in copy_without_quotes");
	dest_index = 0;
	outer_quote = '\0';
	i = 0;
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '\"') && outer_quote == '\0')
			outer_quote = src[i];
		else if (src[i] == outer_quote)
			outer_quote = '\0';
		else
			dest[dest_index++] = src[i];
		++i;
	}
	dest[dest_index] = '\0';
}

void	remove_outer_quotes(char **str)
{
	size_t	new_str_size;
	char	*new_str;

	if (!str)
	{
		print_error(2, "NULL str in remove_outer_quotes");
		return ;
	}
	if (!*str)
	{
		print_error(3, "NULL *str in remove_outer_quotes");
		return ;
	}
	new_str_size = calculate_buffer_size(*str);
	if (ft_strlen(*str) == new_str_size)
		return ;
	new_str = (char *)malloc((new_str_size + 1) * sizeof(char));
	if (!new_str)
	{
		print_error(4, "failed malloc in remove_outer_quotes");
		return ;
	}
	copy_without_quotes(new_str, *str);
	free(*str);
	*str = new_str;
}

void	expand_quotes(t_tree *tree)
{
	t_list	*current;

	if (!tree)
		return ;
	current = tree->list;
	while (current)
	{
		remove_outer_quotes(&current->word);
		current = current->next;
	}
}

void	expand_quotes_all_tree(t_tree *tree)
{
	if (!tree)
		return ;
	expand_quotes_all_tree(tree->left_child);
	expand_quotes(tree);
	expand_quotes_all_tree(tree->right_child);
}
