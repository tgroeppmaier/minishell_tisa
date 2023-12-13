/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:40:25 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/13 09:27:56 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prefill_node(t_tree *tree, char *str, t_sgm sgm, t_data *data)
{
	if (NULL == tree || NULL == data)
	{
		print_error(1, "How is this possible in XXI century? prefill_node");
		return ;
	}
	tree->node = EXEC;
	tree->is_builtin = 0;
	tree->data = data;
	tree->cmd = str;
	tree->left_child = NULL;
	tree->right_child = NULL;
	tree->head = NULL;
	tree->list = NULL;
	tree->beg = sgm.b;
	tree->end = sgm.e;
	tree->level = -1;
	tree->bene = 1;
	tree->do_in_child_process = 1;
	tree->heredoc_cnt = 0;
	tree->heredoc_pipes = NULL;
	tree->gpid = -1;
	return ;
}

/* freeing tree, do not attempt to free data. They are independent entities.
See more in the comments to free_data_except_tree() in builtin_unset.c */
/* It is possible that there is a heredoc_cnt > 0,
 but heredoc pipes were not created because of syntax error. 
So do a double check when freeing */
void	free_tree(t_tree **tree)
{
	int	i;

	if (NULL == tree || NULL == *tree)
		return ;
	free_tree(&(*tree)->left_child);
	free_tree(&(*tree)->right_child);
	(*tree)->head = NULL;
	(*tree)->cmd = NULL;
	(*tree)->data = NULL;
	(*tree)->beg = 0;
	(*tree)->end = 0;
	(*tree)->level = 0;
	(*tree)->node = 0;
	(*tree)->do_in_child_process = 0;
	(*tree)->gpid = 0;
	i = -1;
	while ((*tree)->heredoc_pipes && ++i < (*tree)->heredoc_cnt)
		close((*tree)->heredoc_pipes[i][0]);
	free((*tree)->heredoc_pipes);
	(*tree)->heredoc_pipes = NULL;
	(*tree)->heredoc_cnt = 0;
	ft_free_lst(&(*tree)->list);
	free(*tree);
	*tree = NULL;
	return ;
}

void	print_tree(t_tree *tree)
{
	char	ch_tmp;

	if (NULL == tree || NULL == tree->cmd)
		return ;
	print_tree(tree->left_child);
	ch_tmp = tree->cmd[tree->end];
	tree->cmd[tree->end] = '\0';
	if (EXEC != tree->node)
		ft_printf_fd(STDERR_FILENO, " [l:%d n:%d cmd:{%s} ] ", tree->level, \
			tree->node, &tree->cmd[tree->beg]);
	if (EXEC == tree->node && NULL == tree->list && \
		!is_str_empty(tree->cmd, cr_sgm(tree->beg, tree->end)))
	{
		print_error(-1, "print: still not expanded exec node???");
		ft_printf_fd(STDERR_FILENO, "because[%s]\n\n", &tree->cmd[tree->beg]);
	}
	else if (EXEC == tree->node && tree->list)
	{
		ft_printf_fd(STDERR_FILENO, \
			" [l:%d n:%d cmd:{", tree->level, tree->node);
		ft_print_list(tree->list);
		ft_printf_fd(STDERR_FILENO, "} ] ");
	}
	tree->cmd[tree->end] = ch_tmp;
	print_tree(tree->right_child);
}

// 1: just create
// 2: just print
// 4: just delete
void	create_display_free_tree(t_tree **tree, char *str, int mode, \
							t_data *data)
{
	if (NULL == tree && print_error(1, \
			"create_display_free_tree: NULL tree"))
		return ;
	if (mode & 1)
	{
		create_tree(tree, str, cr_sgm(0, ft_strlen(str)), data);
		set_levels_and_head(*tree);
		if (NULL != *tree && 0 == (*tree)->bene)
			print_error(1, "error parsing the tree: wrong input");
		if (0 != does_grammar_have_mistakes(*tree))
			print_error(2, "error parsing: grammar mistake");
		expand_exec_nodes_count_heredocs(*tree);
		if (0 != do_exec_nodes_have_mistakes(*tree))
			print_error(3, "error parsing: syntax mistake");
		retrieve_bene(*tree);
	}
	if (mode >> 1 & 1)
	{
		ft_printf_fd(STDERR_FILENO, "\n-------TREE----------\n");
		print_tree(*tree);
		ft_printf_fd(STDERR_FILENO, "\n---------------------\n\n");
	}
	if (mode >> 2 & 1)
		free_tree(tree);
	return ;
}
