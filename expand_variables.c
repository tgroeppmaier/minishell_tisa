/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:32:47 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/12 15:27:16 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

/* returns true, if given index is in single quotes*/
bool	in_single_quotes(const char *str, int index)
{
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (str == NULL || index < 0)
		return (false);
	while (str[i] && i <= index)
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote);
}

int	skip_copy(int *i, int *k, char *str, char *expand)
{
	while (str[*i])
	{
		if (str[*i] == '$' && !in_single_quotes(str, *i))
		{
			(*i)++;
			if (!str[*i])
			{
				expand[*k] = '$';
				(*k)++;
				return (1);
			}
			if (str[*i] && (str[*i] == '"' || str[*i] == '\''))
				expand[*k] = str[*i];
			else
				return (0);
		}
		else
			expand[*k] = str[*i];
		(*i)++;
		(*k)++;
		expand[*k] = '\0';
	}
	return (1);
}

/* if first character after $ is not valid (A-Z, a-z or '_') it removes $ and
that character; it takes the name as variable name, as long as the following
characters are valid (A-Z, a-z, 0-9, '_' ). it takes out these characters and
replaces it with the variable value. if the variable does not exist,
these characters will be deleted*/

void	expand_str(t_tree *tree, char *str, char *expand, int len)
{
	int		i;
	int		k;
	char	*var_name;
	char	*var_value;

	i = 0;
	k = 0;
	while (k < len && str[i])
	{
		if (skip_copy(&i, &k, str, expand) == 1)
			continue ;
		var_name = get_var_name(str + i);
		if (var_name == NULL)
			i++;
		else
		{
			var_value = ft_getenv(var_name, tree->data);
			if (var_value != NULL)
				k = ft_strlcat(expand, var_value, len);
			i += ft_strlen(var_name);
			free(var_name);
		}
	}
	expand[k] = '\0';
}

void	expand_variables(t_tree *tree)
{
	t_list	*current;
	char	*expand;
	int		len;

	if (!tree)
		return ;
	current = tree->list;
	while (current)
	{
		len = get_expand_len(tree, current->word, 0, 1);
		expand = (char *)malloc(sizeof(char) * (len + 1));
		if (expand == NULL)
		{
			ft_printf_fd(2, "error in malloc\n");
			return ;
		}
		expand[0] = '\0';
		expand_str(tree, current->word, expand, len);
		free(current->word);
		current->word = expand;
		current = current->next;
	}
}
// 95->105: this will be made bigger after all test to have some margin
// 95->108: this needs to be adjusted of error

void	expand_variables_all_tree(t_tree *tree)
{
	if (!tree)
		return ;
	expand_exit(tree, tree->data->exit_code);
	expand_variables_all_tree(tree->left_child);
	expand_variables(tree);
	expand_variables_all_tree(tree->right_child);
}
