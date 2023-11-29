/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:15:51 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 22:20:20 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char*))
{
	t_size_t	len;

	if (str == NULL)
	{
		return ;
	}
	len = ft_strlen(str);
	while (len > 0)
	{
		f(len - 1, &(str[len - 1]));
		--len;
	}
	return ;
}
