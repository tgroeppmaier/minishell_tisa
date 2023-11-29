/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:56:01 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 21:16:50 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, t_size_t n)
{
	t_size_t	cnt;
	char		*ptr;
	char		*src_ptr;

	ptr = (char *)dest;
	src_ptr = (char *)src;
	cnt = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (cnt < n)
	{
		*ptr = src_ptr[cnt];
		++cnt;
		++ptr;
	}
	return (dest);
}
