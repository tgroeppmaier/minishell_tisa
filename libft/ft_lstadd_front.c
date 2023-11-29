/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:51:51 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/23 17:22:46 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
	return ;
}

/*void	ft_free_lst(t_list **node)
{
	if (NULL == node || NULL == *node)
		return ;
	ft_free_lst(&(*node)->next);
	free((*node)->word);
	(*node)->word = NULL;
	free(*node);
	*node = NULL;
}*/

void	ft_free_lst(t_list **node)
{
	t_list	*node_ptr;
	t_list	*next_node_ptr;

	if (NULL == node || NULL == *node)
		return ;
	node_ptr = *node;
	*node = NULL;
	while (NULL != node_ptr)
	{
		next_node_ptr = node_ptr->next;
		free(node_ptr->word);
		node_ptr->word = NULL;
		free(node_ptr);
		node_ptr = next_node_ptr;
	}
	return ;
}
