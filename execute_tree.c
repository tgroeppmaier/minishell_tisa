/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:04:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 17:24:19 by Ektin Op Urims   ###   ########.fr       */
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
	if (DEBUG_MODE)
		ft_printf_fd(STDERR_FILENO, "Now the tree will be executed!\n");
	if (PIPE == tree->node)
		res = ft_exec_pipe(tree);
	else if (EXEC == tree->node)
		res = ft_exec_exec(tree);
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
