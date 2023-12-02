/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:21:53 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/23 23:01:41 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
	{
		return ;
	}
	if (del != NULL)
	{
		(*del)(lst->word);
		lst->next = NULL;
		free(lst);
	}
	return ;
}

void	ft_lst_del_one_node(t_list **head, t_list *node)
{
	t_list	*ptr;

	if (!head || !head || !node)
		return ;
	if (node == *head)
	{
		*head = node->next;
		basic_free_of_node(node);
		return ;
	}
	ptr = *head;
	while (ptr && ptr->next && ptr->next != node)
		ptr = ptr->next;
	if (!ptr->next)
		return ;
	if (node != ptr->next)
		ft_printf_fd(2, "%sNO: in ft_list_del_one_node%s\n\n", RED, RES);
	ptr->next = ptr->next->next;
	basic_free_of_node(node);
	return ;
}

void	basic_free_of_node(t_list *node)
{
	if (!node)
		return ;
	if (node->word)
	{
		free(node->word);
		node->word = NULL;
	}
	node->is_special_tkn = 0;
	node->next = NULL;
	free(node);
	return ;
}
