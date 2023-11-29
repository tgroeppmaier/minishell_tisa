/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:32:57 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/20 21:27:28 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char ch)
{
	if (ch == ' ' || ('\t' <= ch && ch <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	while (ft_isspace(*str))
	{
		++str;
	}
	sign = 1;
	if (*str == '+')
	{
		++str;
	}
	else if (*str == '-')
	{
		sign = -1;
		++str;
	}
	while (ft_isdigit(*str))
	{
		res *= 10;
		res += *str - '0';
		++str;
	}
	return (sign * res);
}

int	ft_atoi_err(const char *str, int *err)
{
	int	res;
	int	sign;
	int	oldres;
	int	digits_pres;

	digits_pres = 0;
	res = 0;
	*err = 0;
	while (ft_isspace(*str))
		++str;
	deal_with_sign(&str, &sign);
	while (ft_isdigit(*str))
	{
		digits_pres = 1;
		oldres = res;
		res = res * 10 + (*str - '0');
		if (1 == overflow(res, oldres, sign, *str))
			*err = 1;
		++str;
	}
	while (ft_isspace(*str))
		++str;
	if (*str != '\0' || 0 == digits_pres)
		*err = 1;
	return (sign * res);
}

void	deal_with_sign(char const **str, int *sign)
{
	*sign = 1;
	if (**str == '+')
		++(*str);
	else if (**str == '-' && ++(*str))
		*sign = -1;
}

int	overflow(int res, int oldres, int sign, char ch)
{
	if ((res - (ch - '0')) / 10 != oldres || \
		(!(res == -res && -1 == sign) && \
		res < 0 && res - (ch - '0') > 0))
		return (1);
	return (0);
}
