/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_aux_find_symb.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:07:47 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/16 21:04:40 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// beg including, end excluding, beg .. end - 1
int	find_symb(char const *str, char ch, t_sgm sgm)
{
	int	i;

	if (NULL == str || sgm.b >= sgm.e || sgm.b < 0 || \
			(int)ft_strlen(str) < sgm.e)
		return (-1);
	i = sgm.b - 1;
	while (++i < sgm.e)
	{
		if (str[i] == ch)
			return (i);
	}
	return (-1);
}

int	isin(char ch, char const *set)
{
	if (NULL == set)
		return (0);
	while (*set)
	{
		if (ch == *set)
			return (1);
		++set;
	}
	return (0);
}

int	find_setsymb(char const *str, char const *set, t_sgm sgm)
{
	int	i;

	if (NULL == str || NULL == set || sgm.b >= sgm.e || \
			(int)ft_strlen(str) < sgm.e || sgm.b < 0)
		return (-1);
	i = sgm.b - 1;
	while (++i < sgm.e)
	{
		if (isin(str[i], set))
			return (i);
	}
	return (-1);
}
