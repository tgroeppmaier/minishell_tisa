/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:04:34 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/02 05:39:12 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_tree(t_tree *tree)
{
	int	res;

	if (NULL == tree)
		return (0);
	if (0 == tree->bene)
		return (1);
	res = 0;
	if (PIPE == tree->node)
		res = ft_exec_pipe(tree);
	else if (EXEC == tree->node)
	{
		res = exec_int_function(tree);
		if (-1 == res)
			res = ft_exec_exec(tree);
	}
	else if (SEMICOLON == tree->node)
		res = ft_exec_semicolon(tree);
	else if (ANDAND == tree->node)
		res = ft_exec_andand(tree);
	else if (OROR == tree->node)
		res = ft_exec_oror(tree);
	else if (BRACKETS == tree->node)
		res = ft_exec_brackets(tree);
	return (res);
}
