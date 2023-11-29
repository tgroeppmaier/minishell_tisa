/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:06:07 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/01/29 21:35:46 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;
	int		index;
	int		len;
	char	*copy;

	c = (char)c;
	copy = (char *)str;
	len = ft_strlen(copy);
	index = 0;
	while (index < len && str[index] != c)
	{
		++index;
	}
	if (index < len)
	{
		ptr = &(copy[index]);
		return (ptr);
	}
	if (index == len && str[index] == c)
	{
		ptr = &(copy[index]);
		return (ptr);
	}
	return (NULL);
}
