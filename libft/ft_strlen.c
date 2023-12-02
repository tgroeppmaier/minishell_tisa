/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:56:01 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/01 16:55:47 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size_t	ft_strlen(const char *str)
{
	t_size_t	len;

	if (str == NULL)
		return (ft_strlen("(null)"));
	len = 0;
	while (*str++)
	{
		++len;
	}
	return (len);
}

// Timo version. Apparently, size_t is the same as my t_size_t
/*size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return (ptr - str);
}*/
