/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_semicolon_and_or_brackets.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:37:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 17:56:01 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_semicolon(t_tree *tree)
{
	int	res;

	if (NULL == tree || SEMICOLON != tree->node)
		return (print_error(1, "wrong call to ft_exec_semicolon ;"));
	res = ft_execute_tree(tree->left_child);
	if (NULL != tree->right_child)
		res = ft_execute_tree(tree->right_child);
	return (res);
}

int	ft_exec_andand(t_tree *tree)
{
	int	res;

	if (NULL == tree || ANDAND != tree->node)
		return (print_error(1, "wrong call to ft_exec_andand &&"));
	res = ft_execute_tree(tree->left_child);
	if (0 != res)
		return (res);
	res = ft_execute_tree(tree->right_child);
	return (res);
}

int	ft_exec_oror(t_tree *tree)
{
	int	res;

	if (NULL == tree || OROR != tree->node)
		return (print_error(1, "wrong call to ft_exec_oror ||"));
	res = ft_execute_tree(tree->left_child);
	if (0 == res)
		return (res);
	res = ft_execute_tree(tree->right_child);
	return (res);
}

int	ft_exec_brackets(t_tree *tree)
{
	if (NULL == tree || BRACKETS != tree->node)
		return (print_error(1, "wrong call to ft_exec_brackets ()[]{}"));
	return (ft_execute_tree(tree->right_child));
}
