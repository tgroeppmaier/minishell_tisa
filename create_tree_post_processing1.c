/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_post_processing1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:40:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/21 00:19:55 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_empty(char const *str, t_sgm sgm)
{
	int	i;

	if (NULL == str || sgm.b < 0 || sgm.e > (int)ft_strlen(str))
		return (print_error(-1, "could never happen in is_str_empty"));
	i = sgm.b - 1;
	while (++i < sgm.e)
	{
		if (0 == isin(str[i], " \t\n\v\r\f"))
			return (0);
	}
	return (1);
}

void	set_levels_and_head(t_tree *tree)
{
	if (NULL == tree)
		return ;
	if (-1 == tree->level)
	{
		tree->level = 0;
		tree->head = tree;
	}
	if (NULL != tree->left_child)
	{
		tree->left_child->level = tree->level + 1;
		tree->left_child->head = tree->head;
	}
	if (NULL != tree->right_child)
	{
		tree->right_child->level = tree->level + 1;
		tree->right_child->head = tree->head;
	}
	set_levels_and_head(tree->left_child);
	set_levels_and_head(tree->right_child);
	return ;
}

void	retrieve_bene(t_tree *tree)
{
	if (NULL == tree)
		return ;
	if (0 == tree->bene)
		return ;
	retrieve_bene(tree->left_child);
	retrieve_bene(tree->right_child);
	if (NULL != tree->left_child && 0 == tree->left_child->bene)
		tree->bene = 0;
	if (NULL != tree->right_child && 0 == tree->right_child->bene)
		tree->bene = 0;
	return ;
}

int	is_tree_empty(t_tree *tree)
{
	if (NULL == tree)
		return (1);
	if (EXEC == tree->node && \
	1 == is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
		return (1);
	return (0);
}

// 0: OK, 1, 2, 3, ...: not ok
int	does_grammar_have_mistakes(t_tree *tree)
{
	int	res;

	if (NULL == tree)
		return (0);
	if (SEMICOLON == tree->node && 1 == is_tree_empty(tree->left_child))
	{
		tree->bene = 0;
		return (print_error(1, "semicolon grammar problem"));
	}
	if ((PIPE == tree->node || ANDAND == tree->node || OROR == tree->node) && \
	(is_tree_empty(tree->left_child) || is_tree_empty(tree->right_child)))
	{
		tree->bene = 0;
		return (print_error_grammar(2, tree->node));
	}
	res = does_grammar_have_mistakes(tree->left_child);
	if (0 != res)
		return (res);
	res = does_grammar_have_mistakes(tree->right_child);
	if (0 != res)
		return (res);
	return (0);
}
