/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:56:01 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/06/12 20:17:36 by Ektin Op Urims   ###   ########.fr       */
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
