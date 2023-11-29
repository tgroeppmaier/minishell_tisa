/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:57:03 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 14:23:19 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_class(char ch)
{
	if ('c' == ch)
		return (1);
	if ('d' == ch || 'i' == ch)
		return (2);
	if ('u' == ch)
		return (3);
	if ('o' == ch)
		return (4);
	if ('x' == ch)
		return (5);
	if ('X' == ch)
		return (6);
	if ('s' == ch)
		return (10);
	if ('p' == ch)
		return (11);
	if ('%' == ch)
		return (100);
	if ('-' == ch)
		return (1000);
	if ('0' == ch)
		return (1003);
	if ('.' == ch)
		return (1004);
	return (0);
}

int	treat_four(int num, char ch, t_uint *res, int fd)
{
	if (ch == 'c')
		*res += ft_putchar_fd(num, fd);
	else if ((ch == 'd' || ch == 'i') && fd != -3)
		*res += ft_putnbr_fd(num, fd);
	else if ((ch == 'd' || ch == 'i') && fd == -3)
		*res += ft_putnbr_senza_minus_fd(num, 1);
	else if (ch == 'u')
		*res += ft_putnbr_base_fd(num, 10, 1, fd);
	else if (ch == 'o')
		*res += ft_putnbr_base_fd(num, 8, -1, fd);
	else if (ch == 'x')
		*res += ft_putnbr_base_fd(num, 16, -1, fd);
	else if (ch == 'X')
		*res += ft_putnbr_base_fd(num, 16, 1, fd);
	if ((ch == 'd' || ch == 'i') && num < 0)
		return (1);
	return (0);
}

int	treat_eight(char *ptr, char ch, t_uint *res, int fd)
{
	t_long_t	largenum;

	if ('s' == ch)
	{
		*res += ft_putstr_fd(ptr, fd);
	}
	else if (ch == 'p')
	{
		if (ptr == NULL)
		{
			*res += ft_putstr_fd("(nil)", fd);
		}
		else
		{
			largenum = (t_long_t)ptr;
			*res += ft_putstr_fd("0x", fd);
			*res += ft_putnbr_base_fd_long(largenum, 16, -1, fd);
		}
	}
	return (0);
}

int	treat48(va_list *args, char ch, t_uint *res, int fd)
{
	unsigned int	num;
	char			*ptr;
	int				minus;

	minus = 2;
	if (get_class(ch) <= get_class('X') && get_class(ch) >= get_class('c'))
	{
		num = va_arg(*args, int);
		minus = treat_four(num, ch, res, fd);
	}
	else if (get_class(ch) >= get_class('s') && get_class(ch) <= get_class('p'))
	{
		ptr = va_arg(*args, char *);
		minus = treat_eight(ptr, ch, res, fd);
	}
	return (minus);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	t_uint		res;

	va_start(args, str);
	res = 0;
	while (*str != '\0')
	{
		if (*str == '%' && get_class(*(str + 1)) >= get_class('c') \
				&& get_class(*(str + 1)) <= get_class('p'))
		{
			treat48(&args, *(++str), &res, 1);
		}
		else if (*str == '%' && *(str + 1) != '%')
			treatbonus(&args, &str, &res);
		else if (*str == '%' && *(++str) == '%')
			res += ft_putchar_fd('%', 1);
		else
			res += ft_putchar_fd(*str, 1);
		++str;
	}
	va_end(args);
	return (res);
}
