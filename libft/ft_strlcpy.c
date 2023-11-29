/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:43:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/19 19:26:01 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size_t	ft_strlcpy(char *dest, const char *src, t_size_t size)
{
	t_size_t	len_src;
	t_size_t	index;

	len_src = ft_strlen(src);
	index = 0;
	if (size > 0)
	{
		while (index + 1 < size && src[index] != '\0')
		{
			dest[index] = src[index];
			++index;
		}
		dest[index] = '\0';
	}
	return (len_src);
}
