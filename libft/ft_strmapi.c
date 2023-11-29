/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:15:51 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 22:07:57 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	t_size_t	len;
	char		*res;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	while (len > 0)
	{
		res[len - 1] = f(len - 1, str[len - 1]);
		--len;
	}
	return (res);
}
