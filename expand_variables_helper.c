/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:32:36 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/08 20:35:52 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

int	get_varname_len(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_var_name(char *str)
{
	int		len;
	char	*var_name;

	len = get_varname_len(str);
	if (len == 0)
		return (NULL);
	var_name = ft_strndup(str, len);
	return (var_name);
}

/* skips over characters that are not $ or $ followed by quotes
or $ within single quotes and increment len */

int	skip_count(int *i, int *len, char *str)
{
	while (str[*i])
	{
		if (str[*i] == '$' && !in_single_quotes(str, *i))
		{
			if (str[*i + 1] && str[*i + 1] != '"' && str[*i + 1] != '\'')
				return (0);
		}
		(*len)++;
		(*i)++;
	}
	return (1);
}

/* i and len are only passed here because of norminette. i = 0, len = 1 */
/* if first character after $ is not valid (A-Z,
	a-z or '_') it removes $ and that character
it takes the name as variable name,
	as long as the following characters are valid (A-Z, a-z, 0-9, '_' )
it takes out these characters and replaces it with the variable value. if the variable does not exist,
these characters will be deleted*/

int	get_expand_len(t_tree *tree, char *str, int i, int len)
{
	char	*var_name;
	char	*var_value;

	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (skip_count(&i, &len, str) == 1)
			continue ;
		if (!str[++i])
			return (len);
		var_name = get_var_name(str + i);
		if (var_name == NULL) // means invalid char after $
			i++;
		else
		{
			var_value = ft_getenv(var_name, tree->data);
			if (var_value != NULL)
				len += ft_strlen(var_value);
			i += ft_strlen(var_name);
			free(var_name);
		}
	}
	return (len);
}
