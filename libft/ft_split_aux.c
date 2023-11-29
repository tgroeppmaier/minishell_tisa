/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:09:12 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/20 14:10:45 by Ektin Op Urims   ###   ########.fr       */
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
		++j;
	}
	free(arr_str);
}
