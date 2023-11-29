/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:57:03 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/10 12:39:53 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_fd(int fd, const char *str, ...)
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
			treat48(&args, *(++str), &res, fd);
		}
		else if (*str == '%' && *(str + 1) != '%')
			treatbonus(&args, &str, &res);
		else if (*str == '%' && *(++str) == '%')
			res += ft_putchar_fd('%', fd);
		else
			res += ft_putchar_fd(*str, fd);
		++str;
	}
	va_end(args);
	return (res);
}
