/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_aux_find_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:07:47 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/18 14:37:06 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_str(char const *str, char const *tkn, t_sgm sgm)
{
	int	i;
	int	len_tkn;

	if (NULL == str || NULL == tkn || 0 == ft_strlen(tkn) || \
		sgm.b >= sgm.e || sgm.b < 0 || (int)ft_strlen(str) < sgm.e)
		return (-1);
	len_tkn = ft_strlen(tkn);
	i = sgm.b - 1;
	while (++i < sgm.e)
	{
		if (0 == ft_strncmp(&str[i], tkn, len_tkn))
			return (i);
	}
	return (-1);
}

int	is_str_in_setstr(char const *str, char const *const *setstr)
{
	if (NULL == str || NULL == setstr)
		return (0);
	while (NULL != *setstr)
	{
		if (0 == ft_strncmp(str, *setstr, ft_strlen(*setstr)))
			return (ft_strlen(*setstr));
		++setstr;
	}
	return (0);
}

int	find_setstr(char const *str, char const *const *settkn, t_sgm sgm)
{
	int	i;

	if (NULL == str || NULL == settkn || sgm.b >= sgm.e || \
			(int)ft_strlen(str) < sgm.e || sgm.b < 0)
		return (-1);
	i = sgm.b - 1;
	while (++i < sgm.e)
	{
		if (is_str_in_setstr(&str[i], settkn))
			return (i);
	}
	return (-1);
}
