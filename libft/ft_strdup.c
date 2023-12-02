/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:31:16 by Ektin Op Ur       #+#    #+#             */
/*   Updated: 2023/12/01 21:11:23 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(ptr, str, ft_strlen(str) + 1);
	return (ptr);
}
