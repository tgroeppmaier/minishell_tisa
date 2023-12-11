/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:56:01 by aminakov          #+#    #+#             */
/*   Updated: 2023/01/29 21:27:38 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int ch, t_size_t n)
{
	t_size_t	cnt;
	char		*ptr;

	ptr = (char *)str;
	cnt = 0;
	while (cnt < n)
	{
		*ptr = ch;
		++ptr;
		++cnt;
	}
	return (str);
}
