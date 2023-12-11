/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:09:12 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/01 21:48:15 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **arr_str)
{
	int	j;

	if (NULL == arr_str || NULL == *arr_str)
		return ;
	j = 0;
	while (arr_str[j] != NULL)
	{
		free(arr_str[j]);
		arr_str[j] = NULL;
		++j;
	}
	free(arr_str);
}
