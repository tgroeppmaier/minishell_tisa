/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:06:07 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/01/29 21:31:44 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *str, int ch, t_size_t n)
{
	t_size_t	index;
	char		*ptr;

	ptr = str;
	index = 0;
	ch = (char)ch;
	while (index < n)
	{
		if (ptr[index] == ch)
		{
			return (&(ptr[index]));
		}
		++index;
	}
	return (NULL);
}
