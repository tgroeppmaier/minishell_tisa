/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_of_exec_nodes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:02:27 by Ektin Op Ur       #+#    #+#             */
/*   Updated: 2023/12/07 13:00:18 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

int	expand_exec_nodes(t_tree *tree)
{
	char	ch_tmp;

	if (NULL == tree)
		return (print_error(-1, ""));
	if (tree->node == EXEC)
	{
		if (NULL == tree->cmd || tree->beg < 0
			|| tree->end > (int)ft_strlen(tree->cmd))
			return (print_error(-2, "impossible tree in expand_exec-nodes"));
		ch_tmp = tree->cmd[tree->end];
		tree->cmd[tree->end] = '\0';
		tree->list = ft_split_quotes_tkns(&tree->cmd[tree->beg], " \t\n\v\r\f",
				"<< >> >& < > && & || |", "\"'");
		tree->cmd[tree->end] = ch_tmp;
	}
	expand_exec_nodes(tree->left_child);
	expand_exec_nodes(tree->right_child);
	expand_variables(tree);
	// expand_quotes(tree);
	// expand_var_list(tree);
	// ft_print_list(tree->list); // for testing
	return (0);
}
