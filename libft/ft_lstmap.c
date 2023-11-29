/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:31:50 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/18 23:13:53 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*set_node_list(void *content)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list) * 1);
	res->word = content;
	res->next = NULL;
	return (res);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void		*new_curr_content;
	t_list		*new_curr_node;
	t_list		*res;

	if (lst == NULL)
		return (NULL);
	new_curr_content = (*f)(lst->word);
	if (new_curr_content == NULL)
		return (NULL);
	res = set_node_list(new_curr_content);
	new_curr_node = res;
	while (lst->next != NULL)
	{
		new_curr_content = (*f)(lst->next->word);
		if (new_curr_content == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		new_curr_node->next = set_node_list(new_curr_content);
		new_curr_node = new_curr_node->next;
		lst = lst->next;
	}
	return (res);
}
