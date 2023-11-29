/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:17:30 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/02/03 21:56:45 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char ch, char const *collection)
{
	while (*collection)
	{
		if (ch == *collection)
			return (1);
		++collection;
	}
	return (0);
}

static char	*allocate_one(void)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * 1);
	if (res == NULL)
	{
		return (NULL);
	}
	res[0] = '\0';
	return (res);
}

static char	*allocate_multiple(t_size_t start, t_size_t end)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (end - start + 2));
	if (res == NULL)
		return (NULL);
	res[end - start + 1] = '\0';
	return (res);
}

// here first index is original length; and then an auxilliary index
char	*ft_strtrim(char const *str, char const *set)
{
	t_size_t	index;
	t_size_t	start;
	t_size_t	end;
	char		*res;

	if (str == NULL)
		return (NULL);
	index = ft_strlen(str);
	if (index == 0)
		return (allocate_one());
	start = 0;
	while (is_in(str[start], set))
		++start;
	if (start == index)
		return (allocate_one());
	end = index - 1;
	while (is_in(str[end], set))
		--end;
	res = allocate_multiple(start, end);
	if (res == NULL)
		return (NULL);
	index = -1;
	while (++index + start <= end)
		res[index] = str[index + start];
	return (res);
}
