/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:54:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 23:15:26 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(t_size_t num, t_size_t size)
{
	char		*ptr;
	t_size_t	index;
	t_size_t	max;

	if (num == 0 || size == 0)
	{
		return (malloc(0));
	}
	max = (t_size_t)LONG_MAX * 2 + 1;
	max = (t_size_t)LONG_MAX;
	if (max / size < num || (max / size == num && max != size * num))
	{
		return (NULL);
	}
	ptr = (char *)malloc(num * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	index = 0;
	while (index < num * size)
		ptr[index++] = '\0';
	return (ptr);
}
