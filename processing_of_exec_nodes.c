/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_of_exec_nodes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:02:27 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 11:06:53 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_exec_nodes(t_tree *tree)
{
	char	ch_tmp;

	if (NULL == tree)
		return (print_error(-1, ""));
	if (tree->node == EXEC)
	{
		if (NULL == tree->cmd || tree->beg < 0 || \
					tree->end > (int)ft_strlen(tree->cmd))
			return (print_error(-2, "impossible tree in expand_exec-nodes"));
		ch_tmp = tree->cmd[tree->end];
		tree->cmd[tree->end] = '\0';
		tree->list = ft_split_quotes_tkns(&tree->cmd[tree->beg], " \t\n\v\r\f", \
				"<< >> >& < > && & || |", "\"'");
		tree->cmd[tree->end] = ch_tmp;
	}
	expand_exec_nodes(tree->left_child);
	expand_exec_nodes(tree->right_child);
	return (0);
}

int	expand_exec_nodes_count_heredocs(t_tree *tree)
{
	int	cnt;

	expand_exec_nodes(tree);
	cnt = 0;
	return (count_heredocs_in_tree(tree, &cnt));
}

/*BUGS:
	"    "  creates memory leaks: fixed by adding extra check in ft_execute_cmd.
	echo"" | cat -e leads to cmd echo"" not found
		even though echo"" works correctly
	echo "" | cat -e leads to memory leaks and ""$ instead of $
*/
/*
First redirections should be made. Only after that quotes removal should be done.
Redirection is done in two steps. 
First, globally over the whole tree, the << are treated.
Then, in every subtree, locally the redirections are done.
*/
/*int	expand_exec_nodes_together_with_quotes_removal(t_tree *tree)
{
	int	memory_leaks;

	if (0 != expand_exec_nodes_except_treating_quotes(tree))
		return (-1);
	if (DEBUG_MODE)
	{
		create_display_free_tree(&tree, NULL, 2, NULL);
	}
	memory_leaks = 1;
	if (0 == memory_leaks)
		expand_quotes(tree);
	return (0);	
}*/
