/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1_initial_heredoc_treatment.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 22:55:48 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/12 20:01:24 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns -1 on error, or a nonnegative number: number of heredocs
/* calling for both children and then for the node itself works here
because children that have << does not expand to further children */
/* Still, I rearranged it to work more orthodox:
left child, node itslef, right child */
/* This function is called in create_display_free_tree,
and it sets the number of << already there. No need to call for it again.
It assigns a number in is_special_tkn for a heredoc (1, 2, ..., n)
so that we know to which pipe redirect.
There is shift by 1 though (since it starts from 1, not from 0).
And we cannot start from 0, because is_special_tkn == 0
means it is not special. */
/* We will save heredoc_cnt only in the head of the tree. This means that
all call for it should be done through
 tree->head->heredoc_cnt and tree->head->heredoc_pipes */
int	count_heredocs_in_tree(t_tree *tree, int *cnt)
{
	t_list	*node;

	if (!cnt)
		return (print_error(-1, "NULL in count_heredoc"));
	if (!tree)
		return (*cnt);
	count_heredocs_in_tree(tree->left_child, cnt);
	if (EXEC == tree->node && NULL != tree->list)
	{
		node = tree->list;
		while (node)
		{
			if (node->is_special_tkn && 0 == ft_strncmp(node->word, "<<",
					ft_strlen("<<") + 1))
			{
				++(*cnt);
				node->is_special_tkn = *cnt;
				tree->head->heredoc_cnt = *cnt;
			}
			node = node->next;
		}
	}
	count_heredocs_in_tree(tree->right_child, cnt);
	return (*cnt);
}

/* returns 0 if everything is fine, -1, -2, -3 in case of error */
/* should only be called from the head of the tree */
int	create_and_open_pipes_for_heredocs(t_tree *tree)
{
	int	cnt;
	int	res;

	if (!tree)
		return (print_error(-1, "NULL : create_pipes_for_heredocs"));
	if (tree != tree->head)
		return (print_error(-1, "unauth : create_pipes_for_heredocs"));
	res = 0;
	if (0 == tree->heredoc_cnt)
		return (0);
	tree->heredoc_pipes = malloc(sizeof(int[2]) * tree->heredoc_cnt);
	if (NULL == tree->heredoc_pipes)
		return (print_error(-2, "failed malloc in crt pipes <<"));
	cnt = -1;
	while (++cnt < tree->head->heredoc_cnt)
	{
		if (-1 == pipe(tree->head->heredoc_pipes[cnt]))
			res = print_error(-3, "problem opening pipe");
	}
	if (-3 == res)
		close_all_heredoc_pipes_except(tree, -1, -1);
	if (DEBUG_MODE)
		print_pipes_that_were_created(tree);
	return (res);
}

int	print_pipes_that_were_created(t_tree *tree)
{
	int	i;

	if (!tree)
		return (print_error(-1, "NULL in print_pipes"));
	if (0 != tree->head->heredoc_cnt && !tree->head->heredoc_pipes)
		return (print_error(-2, "print_pipes: NULL pipes"));
	if (0 == tree->head->heredoc_cnt && tree->head->heredoc_pipes)
		return (print_error(-2, "print_pipes: not NULL pipes"));
	if (0 == tree->head->heredoc_cnt)
		return (0);
	ft_printf_fd(2, "\n\nPipes:");
	i = -1;
	while (++i < tree->head->heredoc_cnt)
		ft_printf_fd(2, "    pipe[%d]: r=%d;w=%d;\n", i,
			tree->head->heredoc_pipes[i][0], tree->head->heredoc_pipes[i][1]);
	ft_printf_fd(2, "\n\n");
	return (0);
}

// close except r for reading and w for writing
/* call it with -1, -1 if you want to close pipes.
 This function should be called after the execution,
because we do not know which heredocs were needed in the subtree.
Besides, for instance in <<xxx && <<yyy, everything is done in one process.
So when should we close the pipes? Just before freeing everything? */
int	close_all_heredoc_pipes_except(t_tree *tree, int r, int w)
{
	int	index;

	if (NULL == tree)
		return (print_error(-1, "NULL in closeallpipes"));
	if (NULL == tree->head->heredoc_pipes && 0 != tree->head->heredoc_cnt)
		return (print_error(-2, "Impossible in close_all_heredoc pipes"));
	if (NULL == tree->head->heredoc_pipes)
		return (0);
	index = -1;
	while (++index < tree->head->heredoc_cnt)
	{
		if (index != r)
			close(tree->head->heredoc_pipes[index][0]);
		if (index != w)
			close(tree->head->heredoc_pipes[index][1]);
	}
	return (0);
}
