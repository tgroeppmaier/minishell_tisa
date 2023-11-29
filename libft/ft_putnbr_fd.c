/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:09:04 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/07/31 16:58:14 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_set_tens_putnbr_fd(int num, int *tens)
{
	int	res;

	res = 1;
	if (num <= 9 && num >= -9)
	{
		*tens = 1;
	}
	else
	{
		res += ft_set_tens_putnbr_fd(num / 10, tens);
		*tens *= 10;
	}
	return (res);
}

int	ft_putnbr_fd(int n, int fd)
{
	int		tens;
	char	curr_digit;
	int		res;

	res = ft_set_tens_putnbr_fd(n, &tens);
	if (n < 0 && ++res)
	{
		ft_putchar_fd('-', fd);
		if (n == -n)
		{
			curr_digit = -(n / tens);
			ft_putchar_fd(curr_digit + '0', fd);
			n += curr_digit * tens;
			tens /= 10;
		}
		n = -n;
	}
	while (tens > 0)
	{
		curr_digit = n / tens;
		ft_putchar_fd(curr_digit + '0', fd);
		n -= curr_digit * tens;
		tens /= 10;
	}
	return (res);
}

int	ft_putnbr_senza_minus_fd(int n, int fd)
{
	int		tens;
	char	curr_digit;
	int		res;

	res = ft_set_tens_putnbr_fd(n, &tens);
	if (n < 0 && ++res)
	{
		if (n == -n)
		{
			curr_digit = -(n / tens);
			ft_putchar_fd(curr_digit + '0', fd);
			n += curr_digit * tens;
			tens /= 10;
		}
		n = -n;
	}
	while (tens > 0)
	{
		curr_digit = n / tens;
		ft_putchar_fd(curr_digit + '0', fd);
		n -= curr_digit * tens;
		tens /= 10;
	}
	return (res);
}
