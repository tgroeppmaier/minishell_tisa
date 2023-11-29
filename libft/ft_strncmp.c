/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:43:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/20 20:00:14 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if (index == n), then res is always 0?
int	ft_strncmp(const char *str1, const char *str2, t_size_t n)
{
	t_size_t	index;
	int			res;

	res = 0;
	index = 0;
	while (*str1 && *str2 && index < n)
	{
		res = *str1 - *str2;
		if (*str1 == *str2)
		{
			++str1;
			++str2;
			++index;
		}
		else
		{
			return ((unsigned char)*str1 - (unsigned int)*str2);
		}
	}
	if (index == n)
		return (res);
	return ((unsigned char)*str1 - (unsigned int)*str2);
}

/* I wanted to use it in minishell to find setstr from end,\
 but it seems to be avoidable and also not useful
Maybe only in find_last_str, but there I wrote and tested code already
// the last case: strings were shorter than n
// the first case: we compared all n symbals, starting from end
int	ft_strncmp_backward(char const *str1, char const *str2, int n)
{
	int	index;
	int	res;
	int	len1;
	int	len2;

	if (NULL == str || NULL == str)
		return (-10);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	res = 0;
	index = 0;
	while (index < n && len1 >= index + 1 && len2 >= index + 1)
	{
		res = str1[len1 - index - 1] - str2[len2 - index - 1];
		if (0 == res)
			++index;
		else
			return (res);
	}
	if (index == n)
		return (0);
	if (len1 >= index + 1 && len2 >= index + 1)
		ft_pintf("\n\nIt can never happen in ft_strncmp_backward\n\n");	
	if (len1 >= index + 1)
		return ((unsigned char)str1[len1 - index - 1]);
	if (len2 >= index + 1)
		return (-(unsigned char)str2[len1 - index - 1]);
	return (0);
}*/
