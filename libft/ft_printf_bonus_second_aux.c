/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_second_aux.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:33:09 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/07/06 18:25:13 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_bonus_ch(char ch)
{
	if (ch == '-' || ch == '0' || ch == '.' \
		|| ch == '#' || ch == ' ' || ch == '+')
		return (1);
	return (0);
}

int	read_width(const char **str)
{
	int	width;

	width = 0;
	while (ft_isdigit(**str))
	{
		width *= 10;
		width += **str - '0';
		++(*str);
	}
	return (width);
}

int	treat_minus(va_list *args, const char **str, t_uint *res, t_uint width)
{
	t_uint	curr_res;

	if (args == NULL || str == NULL || *str == NULL || res == NULL)
		return (-1);
	curr_res = 0;
	treat48(args, **str, &curr_res, 1);
	*res += curr_res;
	if (curr_res < width)
		while (curr_res++ < width)
			*res += ft_putchar_fd(' ', 1);
	return (0);
}

int	treat_digit(va_list *args, const char **str, t_uint *res, t_uint width)
{
	t_uint		curr_res;
	va_list		copy_args;

	if (args == NULL || str == NULL || *str == NULL || res == NULL)
		return (-1);
	curr_res = 0;
	va_copy(copy_args, *args);
	treat48(&copy_args, **str, &curr_res, -2);
	va_end(copy_args);
	*res += curr_res;
	if (curr_res < width)
		while (curr_res++ < width)
			*res += ft_putchar_fd(' ', 1);
	treat48(args, **str, &curr_res, 1);
	return (0);
}
