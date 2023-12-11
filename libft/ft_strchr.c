/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:06:07 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/01 16:40:24 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// My version
/*char	*ft_strchr(const char *str, int c)
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
}*/

// Timo version, modified for const qualifier
char	*ft_strchr(char const *str, int c)
{
	if (NULL == str)
		return (NULL);
	while (*str)
	{
		if ((char)c == *str)
			return ((char *)str);
		++str;
	}
	if ('\0' == c)
		return ((char *)str);
	return (NULL);
}
