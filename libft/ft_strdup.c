/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:31:16 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 13:17:23 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;

	if (NULL == str)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(ptr, str, ft_strlen(str) + 1);
	return (ptr);
}

// Timo
char	*ft_strndup(char const *s1, size_t n)
{
	char	*str;

	str = (char *)malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}
