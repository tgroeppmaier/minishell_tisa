/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:50:23 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/07/31 16:58:44 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	treatbonus(va_list *args, const char **str, t_uint *res)
{
	char		bon_ch;
	t_uint		width;

	if (str == NULL || *str == NULL || args == NULL || res == NULL)
		return ;
	if (!(**str == '%' \
	&& (is_bonus_ch(*((*str) + 1)) || ft_isdigit(*((*str) + 1)))))
		return ;
	if (is_bonus_ch(*(++(*str))))
		bon_ch = *((*str)++);
	else
		bon_ch = -123;
	width = read_width(str);
	if (bon_ch == '#')
		treat_sharp(args, str, res, width);
	else if (bon_ch == ' ' || bon_ch == '+')
		*res += treat_space_plus(args, str, bon_ch, width);
	else if (bon_ch == '-')
		treat_minus(args, str, res, width);
	else if (bon_ch == '0')
		treat_zero(args, str, res, width);
	else if (bon_ch == -123)
		treat_digit(args, str, res, width);
	else if (bon_ch == '.')
		treat_dot(args, str, res, width);
}

int	treat_dot(va_list *args, const char **str, t_uint *res, t_uint width)
{
	if (args == NULL || str == NULL || *str == NULL || res == NULL)
		return (-1);
	if (**str == 's')
	{
		treat_dot_s(args, res, width);
	}
	else if (get_class(**str) >= get_class('d') \
		&& get_class(**str) <= get_class('X'))
	{
		*res += put_nbr_width(args, str, width, 1);
	}
	return (0);
}

int	treat_dot_s(va_list *args, t_uint *res, t_uint width)
{
	char	*ptr;
	char	*ptrcopy;

	ptr = va_arg(*args, char *);
	if (ft_strlen(ptr) > width)
	{
		ptrcopy = (char *)malloc(sizeof(char) * (width + 1));
		if (ptrcopy != NULL)
		{
			ft_strlcpy(ptrcopy, ptr, width + 1);
			*res += ft_putstr_fd(ptrcopy, 1);
			free(ptrcopy);
		}
	}
	else
	{
		*res += ft_putstr_fd(ptr, 1);
	}
	return (0);
}

void	treat_zero(va_list *args, const char **str, t_uint *res, t_uint width)
{
	*res += put_nbr_width(args, str, width, 0);
	return ;
}

int	put_nbr_width(va_list *args, const char **str, t_uint width, int flag4minus)
{
	t_uint		curr_res;
	va_list		copy_args;
	int			minus;
	int			output_res;

	curr_res = 0;
	va_copy(copy_args, *args);
	minus = 0;
	minus = treat48(&copy_args, **str, &curr_res, -2);
	va_end(copy_args);
	if (flag4minus && minus)
		++width;
	output_res = curr_res;
	if (minus)
		ft_putchar_fd('-', 1);
	if (curr_res < width)
		while (curr_res++ < width)
			output_res += ft_putchar_fd('0', 1);
	if (minus)
		treat48(args, **str, &curr_res, -3);
	else
		treat48(args, **str, &curr_res, 1);
	return (output_res);
}
