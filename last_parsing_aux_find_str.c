/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_aux_find_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:07:47 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/20 22:21:21 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tkn[len_tkn - 1 .. 0] str[i .. i - len_tkn + 1]
int	find_last_str(char const *str, char const *tkn, t_sgm sgm)
{
	int	i;
	int	len_tkn;
	int	num_coincide_symb;
	int	j;

	if (NULL == str || NULL == tkn || 0 == ft_strlen(tkn) || \
		sgm.b >= sgm.e || sgm.b < 0 || (int)ft_strlen(str) < sgm.e)
		return (-1);
	len_tkn = ft_strlen(tkn);
	i = sgm.e;
	while (--i >= sgm.b)
	{
		num_coincide_symb = 0;
		j = i + 1;
		while (--j >= i - len_tkn + 1 && j >= sgm.b)
		{
			if (str[j] == tkn[len_tkn - 1 - i + j])
				++num_coincide_symb;
		}
		if (num_coincide_symb == len_tkn)
			return (i - len_tkn + 1);
	}
	return (-1);
}

// returns the length of the found str in setstr
// if 0, did not find
// mistake should never happen
int	is_end_of_str_in_setstr(char const *str, t_sgm sgm, \
				char const *const *setstr)
{
	int	len;

	if (NULL == str || NULL == setstr)
		return (0);
	if (sgm.e > (int)ft_strlen(str) || sgm.b < 0 || sgm.b >= sgm.e)
	{
		print_error(-1, "could never happen in is_end_of_str_in_setstr");
		return (0);
	}
	while (NULL != *setstr)
	{
		len = ft_strlen(*setstr);
		if (sgm.e >= sgm.b + len && \
			0 == ft_strncmp(&str[sgm.e - len], *setstr, len))
			return (len);
		++setstr;
	}
	return (0);
}

int	find_last_setstr(char const *str, char const *const *settkn, t_sgm sgm)
{
	int	i;
	int	len;

	if (NULL == str || NULL == settkn || sgm.b >= sgm.e || \
			(int)ft_strlen(str) < sgm.e || sgm.b < 0)
		return (-1);
	i = sgm.e + 1;
	while (--i > sgm.b)
	{
		len = is_end_of_str_in_setstr(str, cr_sgm(sgm.b, i), settkn);
		if (len > 0)
			return (i - len);
	}
	return (-1);
}
