/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_of_exec_nodes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:02:27 by Ektin Op Ur       #+#    #+#             */
/*   Updated: 2023/12/01 18:01:36 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void remove_outer_quotes(char *word)
// {
	
// }

void expand_quotes(t_tree *tree)
{
	t_list *current;
	char *tmp;
	
	current = tree->list;
	while(current)
	{
		ft_printf("%s\n", current->word);
		remove_outer_quotes(current->word, tmp);
		current = current->next;
	}
}

int	remove_outer_quotes(char *str, char *tmp)
{
	int		pos_open;
	int		pos_close;
	char	quote;
	t_sgm	sgm;

	sgm.b = 0;
	sgm.e = (int)ft_strlen(str);
	pos_open = 0;

	if (NULL == str || sgm.e == 0)
	{
		return (0);
	}
	while(pos_open < ft_strlen(str))
	{
		pos_open = get_quote_pos(str, sgm);
		if (-1 == pos_open)
			return (0);
		quote = str[pos_open];
		pos_close = find_symb(str, quote, cr_sgm(pos_open + 1, sgm.e));
		tmp = ft_strndup(str + pos_open, pos_close - pos_open);
		ft_strjoin();
	}
	return (parse_quotes(str, cr_sgm(pos_close + 1, sgm.e)));
}


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
	expand_quotes(tree);
	return (0);
}