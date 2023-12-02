/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:06:41 by aminakov          #+#    #+#             */
/*   Updated: 2023/01/24 21:10:25 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*res;

	if (lst == NULL)
		return (NULL);
	res = lst;
	while (res->next != NULL)
	{
		res = res->next;
	}
	return (res);
}
