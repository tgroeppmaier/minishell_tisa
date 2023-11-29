/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:43:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/01/29 19:14:54 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, t_size_t n)
{
	unsigned char		*ptr1;
	unsigned char		*ptr2;
	t_size_t			index;
	int					res;

	index = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (index < n)
	{
		res = ptr1[index] - ptr2[index];
		if (res != 0)
		{
			return (res);
		}
		++index;
	}
	return (0);
}
