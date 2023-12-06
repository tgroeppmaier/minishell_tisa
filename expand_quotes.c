/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:23:12 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/06 09:23:13 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

size_t	calculate_buffer_size(const char *str)
{
	size_t	size;
	char	outer_quote;
	size_t	i;

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

char	*remove_outer_quotes(const char *str)
{
	size_t	new_str_size;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str_size = calculate_buffer_size(str);
	new_str = malloc(new_str_size + 1);
	if (!new_str)
		return (NULL);
	copy_without_quotes(new_str, str);
	return (new_str);
}

void	expand_quotes(t_tree *tree)
{
	t_list	*current;
	char	*tmp;

	current = tree->list;
	while (current)
	{
		tmp = remove_outer_quotes(current->word);
		if (tmp == NULL)
		{
			ft_printf_fd(2, "error removing outer quotes\n");
			// what to do in this case?
			current = current->next;
			continue ;
		}
		free(current->word);
		current->word = tmp;
		current = current->next;
		// ft_printf("%s\n", current->word);    // for testing
	}
}
