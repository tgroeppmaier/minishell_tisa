/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:50:23 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/07/06 18:18:32 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	treat_sharp(va_list *args, const char **str, t_uint *res, t_uint width)
{
	t_uint		num;
	char		char4base;
	int			fd;
	t_uint		curr_res;

	fd = 1;
	if (get_class(**str) <= get_class('X') \
		&& get_class(**str) >= get_class('o'))
	{
		char4base = **str;
		num = va_arg(*args, t_uint);
		fd = -2;
		curr_res = ft_putoxx_fd(num, char4base, fd);
		*res += curr_res;
		if (curr_res < width)
			while (curr_res++ < width)
				*res += ft_putchar_fd(' ', 1);
		fd = 1;
		ft_putoxx_fd(num, char4base, fd);
	}
	return ;
}

t_uint	ft_putoxx_fd(t_uint num, char char4base, int fd)
{
	t_uint	curr_res;

	curr_res = 0;
	if (num == 0)
	{
	}
	else if (char4base == 'o')
		curr_res += ft_putstr_fd("0", fd);
	else if (char4base == 'x')
		curr_res += ft_putstr_fd("0x", fd);
	else if (char4base == 'X')
		curr_res += ft_putstr_fd("0X", fd);
	treat_four(num, char4base, &curr_res, fd);
	return (curr_res);
}

int	work_space_plus_fd(va_list *args, const char **str, char symb, int fd)
{
	int				num;
	char			*ptr;
	t_uint			curr_res;

	curr_res = 0;
	if (**str == 'd' || **str == 'i')
	{
		num = va_arg(*args, int);
		if (num >= 0)
			curr_res += ft_putchar_fd(symb, fd);
		curr_res += ft_putnbr_fd(num, fd);
	}
	else if (**str == 's')
	{
		ptr = va_arg(*args, char *);
		if (ptr != NULL && ft_strlen(ptr) == 0 && ft_strlen(ptr) > 0)
			curr_res += ft_putstr_fd(" ", fd);
		else
			curr_res += ft_putstr_fd(ptr, fd);
	}
	return (curr_res);
}

t_uint	treat_space_plus(va_list *args, const char **str, \
					char symb, t_uint width)
{
	t_uint		curr_res;
	va_list		args_copy;
	t_uint		output_res;

	va_copy(args_copy, *args);
	curr_res = work_space_plus_fd(&args_copy, str, symb, -2);
	va_end(args_copy);
	output_res = curr_res;
	if (curr_res < width)
		while (curr_res++ < width)
			output_res += ft_putchar_fd(' ', 1);
	work_space_plus_fd(args, str, symb, 1);
	return (output_res);
}
