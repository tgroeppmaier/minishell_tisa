/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:09:04 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/06/12 21:42:36 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_set_pows_putnbr_fd(unsigned int num, unsigned int *pows, \
				unsigned int base)
{
	unsigned int	res;

	res = 1;
	if (num <= base - 1)
	{
		*pows = 1;
	}
	else
	{
		res += ft_set_pows_putnbr_fd(num / base, pows, base);
		*pows *= base;
	}
	return (res);
}

int	ft_putnbr_base_fd(unsigned int n, unsigned int base, int upperlower, int fd)
{
	unsigned int	pows;
	char			curr_digit;
	int				res;

	res = ft_set_pows_putnbr_fd(n, &pows, base);
	while (pows > 0)
	{
		curr_digit = n / pows;
		place_digit(curr_digit, upperlower, fd);
		n -= curr_digit * pows;
		pows /= base;
	}
	return (res);
}

int	ft_set_pows_putnbr_fd_long(t_long_t num, t_long_t *pows, \
				t_long_t base)
{
	t_long_t	res;

	res = 1;
	if (num <= base - 1)
	{
		*pows = 1;
	}
	else
	{
		res += ft_set_pows_putnbr_fd_long(num / base, pows, base);
		*pows *= base;
	}
	return (res);
}

int	ft_putnbr_base_fd_long(t_long_t n, t_long_t base, int upperlower, int fd)
{
	t_long_t	pows;
	char		curr_digit;
	int			res;

	res = ft_set_pows_putnbr_fd_long(n, &pows, base);
	while (pows > 0)
	{
		curr_digit = n / pows;
		place_digit(curr_digit, upperlower, fd);
		n -= curr_digit * pows;
		pows /= base;
	}
	return (res);
}

int	place_digit(int digit, int upperlower, int fd)
{
	if (0 <= digit && digit <= 9)
	{
		ft_putchar_fd(digit + '0', fd);
		return (0);
	}
	if (10 <= digit && digit <= 'z' - 'a' + 10)
	{
		if (upperlower == -1)
			ft_putchar_fd(digit - 10 + 'a', fd);
		else
			ft_putchar_fd(digit - 10 + 'A', fd);
		return (0);
	}
	return (1);
}
