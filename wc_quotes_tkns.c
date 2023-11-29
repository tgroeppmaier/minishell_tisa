/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_quotes_tkns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:15:51 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/19 18:10:40 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_words_quotes_tkns(char const *str, char const *spaces, \
				char const *tkns, char const *quotes)
{
	int		i;
	int		wc;
	char	**tkns_arr;

	if (NULL == str || 0 == ft_strlen(str))
		return (0);
	tkns_arr = ft_split(tkns, ' ');
	wc = 0;
	i = 0;
	while ('\0' != str[i] && '\n' != str[i])
	{
		if (isin(str[i], spaces) && wc_pass_spaces(str, spaces, &i))
			continue ;
		if (wc_pass_tkn(str, (char const *const *)tkns_arr, &i, &wc))
			continue ;
		++wc;
		--i;
		while (str[++i] && 0 == isin(str[i], spaces) && \
			0 == is_str_in_setstr(&str[i], (char const *const *)tkns_arr))
			if (isin(str[i], quotes) && -1 == \
				wc_pass_quotes(str, quotes, &tkns_arr, &i))
				return (-1);
	}
	return (wc_free_print_ft_split(&tkns_arr, wc, NULL));
}

int	wc_pass_spaces(char const *str, char const *spaces, int *i)
{
	if (NULL == str || NULL == i)
		return (1);
	while (isin(str[*i], spaces))
		++(*i);
	return (1);
}

int	wc_pass_tkn(char const *str, char const *const *tkns_arr, int *i, int *wc)
{
	int	len_tkn;

	if (NULL == str || NULL == tkns_arr || NULL == i || NULL == wc)
		return (0);
	len_tkn = is_str_in_setstr(&str[*i], tkns_arr);
	if (0 == len_tkn)
		return (0);
	++(*wc);
	*i += len_tkn;
	return (1);
}

int	wc_pass_quotes(char const *str, char const *quotes, \
					char ***tkns_arr, int *i)
{
	char	quote;

	if (NULL == str || NULL == quotes || NULL == i)
		return (0);
	quote = str[*i];
	while (str[*i + 1] && str[*i + 1] != quote)
		++(*i);
	if ('\0' == str[*i + 1])
		return (wc_free_print_ft_split(tkns_arr, -1, "unclosed quote"));
	++(*i);
	return (0);
}

int	wc_free_print_ft_split(char ***tkns_arr, int res, char const *msg)
{
	if (NULL == tkns_arr)
		return (print_error(-1, "wrong input in free_print_ft_split"));
	free_split(*tkns_arr);
	*tkns_arr = NULL;
	if (res < 0)
		return (print_error(res, msg));
	return (res);
}
