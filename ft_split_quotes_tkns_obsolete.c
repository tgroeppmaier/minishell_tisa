/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_tkns_obsolete.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:20:13 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/18 15:32:09 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_words_quotes_tkns(char const *str, char const *spaces, \
				char const *tkns, char const *quotes)
{
	int		isquoted;
	int		i;
	int		cnt;
	char	quote;
	char	**tkns_arr;
	t_sgm	sgm;
	int		len_tkn;

	if (NULL == str || 0 == ft_strlen(str))
		return (0);
	sgm.b = 0;
	sgm.e = 0;
	tkns_arr = ft_split(tkns, ' ');
	cnt = 0;
	isquoted = 0;
	i = -1;
	while ('\0' != str[++i])
	{
		if (1 == isin(str[i], quotes))
		{
			if (0 == isquoted)
			{
				isquoted = 1;
				quote = str[i];
				sgm.b = i;
			}
			else if (1 == isquoted)
			{
				if (quote == str[i])
				{
					isquoted = 0;
					ft_printf("increase cnt1, i=[%d]\n", i);
					sgm.e = i + 1;
					sgm.b = i + 1;
					++cnt;
				}
			}
		}
		else if (1 == isin(str[i], spaces))
		{
			//++sgm.b;
			if (i > 0 && 0 == isin(str[i - 1], spaces))
			{
				ft_printf("increase cnt2, i=[%d]\n", i);
				++cnt;
			}
		}
		else
		{
			len_tkn = is_str_in_setstr(&str[i], \
				(char const* const*)tkns_arr);
			if (len_tkn)
			{
				ft_printf("found token\n");
				if (i > 0 && 0 == isin(str[i - 1], spaces))
				{
					ft_printf("increase cnt3, i=[%d]\n", i);
					++cnt;
				}
				i += is_str_in_setstr(&str[i], \
					(char const* const *)tkns_arr) - 1;
				/*{
					ft_printf("increase cnt4, i=[%d]\n", i);
					++cnt;
				}*/
			}
		}
	}
	if (i > 0 && '\0' == str[i] && 0 == isin(str[i-1], spaces))
	{
		ft_printf("increase cnt5, i=[%d]\n", i);
		++cnt;
	}
	free_split(tkns_arr);
	tkns_arr = NULL;
	return (cnt);
}
