/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:53:36 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 21:01:19 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, t_size_t len)
{
	unsigned int	real_len;
	char			*res_ptr;

	if (str == NULL)
		return (NULL);
	if ((t_size_t)start > ft_strlen(str))
	{
		res_ptr = (char *)malloc(1);
		*res_ptr = '\0';
		return (res_ptr);
	}
	real_len = ft_strlen(&(str[start]));
	if (real_len > len)
	{
		real_len = len;
	}
	res_ptr = (char *)malloc(sizeof(char) * real_len + 1);
	if (res_ptr == NULL)
		return (NULL);
	ft_strlcpy(res_ptr, &(str[start]), real_len + 1);
	return (res_ptr);
}
