/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:56:01 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 23:07:39 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Tomas Kajanek said it can be rewritten without 
blocking additional space by acting from end*/
void	*ft_memmove(void *dest, const void *src, t_size_t n)
{
	char		*dest_ptr;
	char		*src_ptr;
	t_size_t	index;

	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	index = 0;
	while (index < n)
	{
		*(dest_ptr + n - 1 - index) = *(src_ptr + n - 1 - index);
		++index;
	}
	return (dest);
}
