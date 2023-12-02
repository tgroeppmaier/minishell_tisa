/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_0x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:32:57 by aminakov          #+#    #+#             */
/*   Updated: 2023/08/20 22:00:07 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_generalized_digit(char ch)
{
	if ('0' <= ch && ch <= '9')
		return (1);
	if ('a' <= ch && ch <= 'f')
		return (1);
	if ('A' <= ch && ch <= 'F')
		return (1);
	return (0);
}

int	ft_atoi_0x(const char *str)
{
	int	res;

	res = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
	{
		str += 2;
	}
	while (ft_is_generalized_digit(*str))
	{
		res <<= 4;
		if ('0' <= *str && *str <= '9')
			res += *str - '0';
		else if ('a' <= *str && *str <= 'f')
			res += *str - 'a' + 10;
		else if ('A' <= *str && *str <= 'F')
			res += *str - 'A' + 10;
		++str;
	}
	return (res);
}
