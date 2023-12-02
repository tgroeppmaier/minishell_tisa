/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:43:06 by aminakov          #+#    #+#             */
/*   Updated: 2023/08/20 19:32:14 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size_t	ft_wc(char const *str, char ch)
{
	t_size_t	wc;

	wc = 0;
	while (*str)
	{
		while (*str == ch)
		{
			++str;
		}
		if ('\0' == *str || '\n' == *str)
		{
			return (wc);
		}
		++wc;
		while (*str != '\0' && *str != ch)
		{
			++str;
		}
	}
	return (wc);
}

t_size_t	ft_len_till_delimiter(const char *str, char ch)
{
	t_size_t	res;

	res = 0;
	while (*str != '\0' && *str != ch)
	{
		++str;
		++res;
	}
	return (res);
}

t_size_t	ft_copy(char *dest, char const *src, char delimiter)
{
	t_size_t	len;

	len = 0;
	while (*src == delimiter)
	{
		++src;
		++len;
	}
	while (*src != '\0' && *src != delimiter)
	{
		*dest = *src;
		++dest;
		++src;
		++len;
	}
	*dest = '\0';
	return (len);
}

static char	**allocate_space_for_res_arr(t_size_t wc)
{
	char	**res_arr;

	res_arr = (char **)malloc(sizeof(char *) * (wc + 1));
	if (res_arr == NULL)
		return (NULL);
	res_arr[wc] = NULL;
	return (res_arr);
}

char	**ft_split(char const *str, char ch)
{
	t_size_t	wc;
	char		**res_arr;
	t_size_t	word_index;
	t_size_t	curr_len;

	if (str == NULL)
		return (NULL);
	wc = ft_wc(str, ch);
	res_arr = allocate_space_for_res_arr(wc);
	if (res_arr == NULL)
		return (NULL);
	word_index = 0;
	while (word_index < wc)
	{
		while (*str == ch)
		{
			++str;
		}
		curr_len = ft_len_till_delimiter(str, ch);
		res_arr[word_index] = (char *)malloc(sizeof(char) * curr_len + 1);
		res_arr[word_index][curr_len] = '\0';
		str += sizeof(char) * ft_copy(res_arr[word_index], str, ch);
		++word_index;
	}
	return (res_arr);
}
