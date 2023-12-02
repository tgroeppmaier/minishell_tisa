/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/29 11:15:56 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_res_in_do_redir_other(t_list *ptr, int last_heredoc)
{
	int	res;

	if (NULL == ptr)
		return (print_error(-1, \
			"cannot happen in assign_res_in_do_redir_other"));
	res = -1;
	if (!ft_strncmp(ptr->word, ">>", 2))
		res = do_redir_outout_biggerbigger(ptr->next->word);
	else if (!ft_strncmp(ptr->word, "<", 1))
		res = do_redir_in_smaller(ptr->next->word, last_heredoc);
	else if (!ft_strncmp(ptr->word, ">", 1))
		res = do_redir_out_bigger(ptr->next->word);
	return (res);
}

/* Again, first should compare with >>, <<, and then with >, <.
Otherwise, << will always be treated as < */
/* << has a higher priority than <, >, >>
so we need to separate the function in two pieces */
int	do_redirections_other(t_tree *tree, int last_heredoc)
{
	t_list	*ptr;
	t_list	*ptr2;
	int		res;

	if (NULL == tree || EXEC != tree->node || NULL == tree->list)
		return (print_error(1, "wrong call to do_redirections_other"));
	ptr = tree->list;
	res = 0;
	while (ptr)
	{
		if (ptr->is_special_tkn && ptr->next)
		{
			res = assign_res_in_do_redir_other(ptr, last_heredoc);
			if (res)
				return (res);
			ptr2 = ptr->next->next;
			ft_lst_del_one_node(&tree->list, ptr->next);
			ft_lst_del_one_node(&tree->list, ptr);
			ptr = ptr2;
		}
		else
			ptr = ptr->next;
	}
	return (0);
}

int	do_redirections_heredoc(t_tree *tree)
{
	t_list	*ptr;
	t_list	*ptr2;
	int		res;

	if (NULL == tree || EXEC != tree->node || NULL == tree->list)
		return (print_error(1, "wrong call to heredoc"));
	ptr = tree->list;
	while (ptr)
	{
		if (ptr->is_special_tkn && ptr->next && !ft_strncmp(ptr->word, "<<", 2))
		{
			res = do_redir_inin_smallersmaller(ptr->next->word, tree);
			if (res)
				return (res);
			ptr2 = ptr->next->next;
			ft_lst_del_one_node(&tree->list, ptr->next);
			ft_lst_del_one_node(&tree->list, ptr);
			ptr = ptr2;
			if (DEBUG_MODE)
				print_tree(tree);
		}
		else
			ptr = ptr->next;
	}
	return (0);
}

/* if the last among all the {>, >>} is heredoc,
I will not do redirections in >. */

int	do_redirections(t_tree *tree)
{
	int		res;
	int		last_heredoc;

	if (NULL == tree || EXEC != tree->node || NULL == tree->list)
		return (print_error(1, "wrong call to do_redirections"));
	last_heredoc = is_last_heredoc(tree);
	if (DEBUG_MODE)
		ft_printf("\n\nlastheredoc is [%d]\n\n\n", last_heredoc);
	res = do_redirections_heredoc(tree);
	if (res)
		return (res);
	if (tree->list)
	{
		res = do_redirections_other(tree, last_heredoc);
		if (res)
			return (res);
	}
	return (0);
}

// if the result is -1, then there are no redirections <, <<
int	is_last_heredoc(t_tree *tree)
{
	t_list	*ptr;
	int		res;

	if (NULL == tree || EXEC != tree->node || NULL == tree->list)
		return (print_error(-1, "wrong call to is_last_heredoc"));
	ptr = tree->list;
	res = -1;
	while (ptr)
	{
		if (ptr->is_special_tkn && ptr->next)
		{
			if (!ft_strncmp(ptr->word, "<<", 2))
				res = 1;
			else if (!ft_strncmp(ptr->word, "<", 1))
				res = 0;
			ptr = ptr->next->next;
		}
		else
			ptr = ptr->next;
	}
	return (res);
}
