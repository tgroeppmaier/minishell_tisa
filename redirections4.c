/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:19 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/10 10:02:34 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Dec 8, 2023: 
1. changed ft_strncmp(ptr->word, ">>", 2) 
to ft_strncmp(ptr->word, ">>", 3) and etc for <, >;
2. added check that the token is special: after removing quotes "<<" 
becomes <<, but should not be treated as a redirection */
/* Dec9,2023: this double check was reduntant, because the function
is called from do_redirections only in the case of is_special_tkn */
static int	assign_res_in_do_redir(t_list *ptr, t_tree *tree)
{
	int	res;

	if (NULL == ptr)
		return (print_error(-1, \
			"cannot happen in assign_res_in_do_redir_other"));
	res = -1;
	if (ptr->is_special_tkn && 0 == ft_strncmp(ptr->word, ">>", 3))
		res = do_redir_outout_biggerbigger(ptr->next->word);
	else if (ptr->is_special_tkn && 0 == ft_strncmp(ptr->word, "<<", 3))
		res = do_redir_inin_part2_read_from_pipe(ptr->is_special_tkn - 1, tree);
	else if (ptr->is_special_tkn && !ft_strncmp(ptr->word, "<", 2))
		res = do_redir_in_smaller(ptr->next->word);
	else if (ptr->is_special_tkn && !ft_strncmp(ptr->word, ">", 2))
		res = do_redir_out_bigger(ptr->next->word);
	return (res);
}

/* Again, first should compare with >>, <<, and then with >, <.
Otherwise, << will always be treated as < */
/* 9Dec2023: I don't think so, because >>, <<, >, < are already in the list, 
meaning they are full-right strings, so we can compare len + 1 symbols there */
/* << has a higher priority than <, >, >>
so we need to separate the function in two pieces */
/* 9Dec2023: not anymore, because they have already been pretreated:
 sent to pipes */
int	do_redirections(t_tree *tree)
{
	t_list	*ptr;
	t_list	*ptr2;
	int		res;

	if (NULL == tree || EXEC != tree->node || NULL == tree->list)
		return (print_error(1, "wrong call to do_redirections"));
	ptr = tree->list;
	res = 0;
	while (ptr)
	{
		if (ptr->is_special_tkn && ptr->next)
		{
			res = assign_res_in_do_redir(ptr, tree);
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
