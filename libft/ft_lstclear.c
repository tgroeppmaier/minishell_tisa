/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:35:07 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/01/30 23:47:48 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		return ;
	}
	if ((*lst)->next == NULL)
	{
		ft_lstdelone(*lst, del);
		*lst = NULL;
		return ;
	}
	ft_lstclear(&((*lst)->next), del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
	return ;
}
