/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:06:01 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/02 09:39:48 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate(t_size_t len1, t_size_t len2)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL)
		return (NULL);
	res[len1 + len2] = '\0';
	return (res);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	t_size_t	len1;
	t_size_t	len2;
	char		*res;
	t_size_t	index;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	res = allocate(len1, len2);
	if (res == NULL)
		return (NULL);
	index = -1;
	while (++index < len1)
		res[index] = str1[index];
	index = -1;
	while (++index < len2)
		res[len1 + index] = str2[index];
	res[len1 + len2] = '\0';
	return (res);
}
