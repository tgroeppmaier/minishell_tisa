/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_aux_find_symb.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:07:47 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/20 17:10:05 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// beg including, end excluding, beg .. end - 1
int	find_last_symb(char const *str, char ch, t_sgm sgm)
{
	int	i;

	if (NULL == str || sgm.b >= sgm.e || sgm.b < 0 || \
			(int)ft_strlen(str) < sgm.e)
		return (-1);
	i = sgm.e;
	while (--i >= sgm.b)
	{
		if (str[i] == ch)
			return (i);
	}
	return (-1);
}

int	find_last_setsymb(char const *str, char const *set, t_sgm sgm)
{
	int	i;

	if (NULL == str || NULL == set || sgm.b >= sgm.e || \
			(int)ft_strlen(str) < sgm.e || sgm.b < 0)
		return (-1);
	i = sgm.e;
	while (--i >= sgm.b)
	{
		if (isin(str[i], set))
			return (i);
	}
	return (-1);
}
