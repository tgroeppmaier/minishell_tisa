/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:00:48 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/08 13:08:01 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	res;

	res = 0;
	if (NULL == str)
	{
		res = ft_putstr_fd("(null)", fd);
		return (res);
	}
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		++str;
		++res;
	}
	return (res);
}
