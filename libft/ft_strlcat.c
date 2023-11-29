/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:43:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 21:28:22 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size_t	ft_strlcat(char *dest, const char *src, t_size_t size)
{
	t_size_t	len_src;
	t_size_t	len_dest;
	t_size_t	index;

	if ((src == NULL && dest == NULL) || (dest == NULL && size == 0))
		return (-1);
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (size > len_dest)
	{
		index = 0;
		while (index < size - len_dest - 1 && src[index] != '\0')
		{
			dest[len_dest + index] = src[index];
			++index;
		}
		dest[len_dest + index] = '\0';
	}
	if (size < len_dest)
	{
		return (size + len_src);
	}
	return (len_src + len_dest);
}
