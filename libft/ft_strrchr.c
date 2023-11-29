/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:06:07 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/01/29 21:39:05 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	index;
	int	len;

	len = ft_strlen(str);
	c = (char)c;
	if (c == '\0')
	{
		return (str + len);
	}
	index = 0;
	while (index < len && str[len - 1 - index] != c)
	{
		++index;
	}
	if (index < len)
		return (&(str[len - 1 - index]));
	return (NULL);
}
