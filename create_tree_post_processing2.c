/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_post_processing2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:40:25 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/20 10:10:59 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	does_list_have_mistakes(t_list *list)
{
	while (NULL != list)
	{
		if (list->is_special_tkn && \
			(NULL == list->next || list->next->is_special_tkn))
			return (print_error_syntax(1, list));
		list = list->next;
	}
	return (0);
}

int	do_exec_nodes_have_mistakes(t_tree *tree)
{
	int	res;

	if (NULL == tree)
		return (0);
	if (EXEC == tree->node)
	{
		if (NULL == tree->list && \
				!is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
			print_error(1, "NULL tree->list in exec node???");
		res = does_list_have_mistakes(tree->list);
		if (0 != res)
		{
			tree->bene = 0;
			return (res);
		}
	}
	res = do_exec_nodes_have_mistakes(tree->left_child);
	if (0 != res)
		return (res);
	res = do_exec_nodes_have_mistakes(tree->right_child);
	if (0 != res)
		return (res);
	return (0);
}
