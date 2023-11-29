/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:40:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 11:17:46 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not good to write if (sgm.b >= sgm.e || 1 == is_str_empty(str, sgm))
// because of ((cmd)) and ((cmd) ) are different staff for bash
// better to check after the tree is constructed
int	create_tree(t_tree **tree, char *str, t_sgm sgm, char *envp[])
{
	int		sep_pos;
	t_node	sep;
	t_sgm	brackets;

	if (NULL == tree || NULL == str || sgm.b < 0 || sgm.e > (int)ft_strlen(str))
		return (print_error(1, "create_tree: wrong input"));
	if (*tree != NULL)
		return (print_error(2, "create_tree: non empty tree is given"));
	if (sgm.b >= sgm.e && DEBUG_MODE)
		return (print_error(0, "create_tree: nothing to be done"));
	if (sgm.b >= sgm.e && 0 == DEBUG_MODE)
		return (0);
	*tree = (t_tree *)malloc(sizeof(t_tree));
	if (NULL == tree)
		return (print_error(3, "create_tree: malloc failed"));
	prefill_node(*tree, str, sgm, envp);
	sep_pos = set_separate_pos(str, sgm, &sep);
	if (-1 != sep_pos)
		return (do_if_sep(*tree, sep_pos, sep));
	sep_pos = set_brackets_pos(str, sgm, &brackets);
	if (0 > sep_pos)
		(*tree)->bene = 0;
	if (0 >= sep_pos)
		return (sep_pos);
	return (doifbrackets_in_create_tree(*tree, brackets));
}

int	do_if_sep(t_tree *tree, int sep_pos, t_node sep)
{
	if (NULL == tree)
		return (print_error(1, "do_if_sep: NULL tree"));
	create_tree(&tree->left_child, tree->cmd, \
			cr_sgm(tree->beg, sep_pos), tree->envp);
	create_tree(&tree->right_child, tree->cmd, \
		cr_sgm(sep_pos + len_sep(sep), tree->end), tree->envp);
	tree->beg = sep_pos;
	tree->end = sep_pos + len_sep(sep);
	tree->node = sep;
	return (0);
}

int	doifbrackets_in_create_tree(t_tree *tree, t_sgm brackets)
{
	if (NULL == tree)
	{
		print_error(1, "doifbrackets_in_create_tree: NULL tree");
		return (1);
	}
	create_tree(&tree->right_child, tree->cmd, \
		cr_sgm(brackets.b + 1, brackets.e), tree->envp);
	tree->beg = brackets.b;
	tree->end = brackets.e + 1;
	tree->node = BRACKETS;
	return (0);
}

int	set_separate_pos(char const *str, t_sgm sgm, t_node *sep)
{
	int		sep_pos;
	char	**settkn;

	if (-1 == check_input_str_sgm(str, sgm))
		return (-1);
	sep_pos = find_sep_semicolon(str, sgm, sep);
	if (-1 != sep_pos)
		return (sep_pos);
	settkn = ft_split("&& ||", ' ');
	sep_pos = find_last_not_quoted_not_bracketed_setstr(str, \
				(char const *const *)settkn, sgm);
	if (-1 != sep_pos)
	{
		if (0 == ft_strncmp(&str[sep_pos], "&&", 2))
			*sep = ANDAND;
		else if (0 == ft_strncmp(&str[sep_pos], "||", 2))
			*sep = OROR;
		free_split(settkn);
		return (sep_pos);
	}
	free_split(settkn);
	sep_pos = find_sep_pipe(str, sgm, sep);
	if (-1 != sep_pos)
		return (sep_pos);
	return (-1);
}

int	check_input_str_sgm(char const *str, t_sgm sgm)
{
	if (NULL == str || sgm.b >= sgm.e || sgm.b < 0 || \
			sgm.e > (int)ft_strlen(str))
		return (-1);
	return (0);
}
