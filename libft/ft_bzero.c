/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:56:01 by aminakov          #+#    #+#             */
/*   Updated: 2023/01/29 21:26:48 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, t_size_t n)
{
	char		*ptr;
	t_size_t	cnt;

	ptr = (char *)str;
	cnt = 0;
	while (cnt < n)
	{
		*ptr = '\0';
		++cnt;
		++ptr;
	}
	return ;
}
