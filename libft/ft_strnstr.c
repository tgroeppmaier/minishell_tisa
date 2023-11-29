/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:43:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 21:39:38 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, t_size_t len)
{
	char		*cp_big;
	t_size_t	index;
	t_size_t	j;
	t_size_t	little_size;
	t_size_t	k;

	cp_big = (char *) big;
	if (big == NULL && len == 0)
		return (NULL);
	if (*little == '\0')
		return (cp_big);
	little_size = ft_strlen(little);
	index = 0;
	k = index + little_size;
	while (k <= ft_strlen(cp_big) && k <= len)
	{
		j = 0;
		while (j < little_size && cp_big[index + j] == little[j])
			++j;
		if (j == little_size)
			return (&(cp_big[index]));
		++index;
		k = index + little_size;
	}
	return (NULL);
}
