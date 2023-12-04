/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_of_exec_nodes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:02:27 by Ektin Op Ur       #+#    #+#             */
/*   Updated: 2023/12/04 18:14:02 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

// 	if (pos_open != -1)
// 	{
// 		quote = str[pos_open];
// 		pos_close = find_symb(str, quote, cr_sgm(pos_open + 1, sgm.e));
// 		if(pos_close == pos_open + 1)
// 		{
// 			// ft_printf("test:%sword", ft_strdup(""));
// 			return(ft_strdup(""));
// 		}
// 	}

char *remove_outer_quotes(char *str) 
{
    int pos_open, pos_close;
    char quote;
    char *tmp1;
    t_sgm sgm;
    char *new_str;
    int i = 0;

	new_str = ft_strdup("");
	if(!new_str)
		return(NULL);
    sgm.e = (int)ft_strlen(str);
    if (sgm.e < 2) 
	{
        free(new_str);
        return (ft_strdup(str));
    }

    while (i < sgm.e) 
	{
        sgm.b = i;
        pos_open = get_quote_pos(str, sgm);
        if (-1 == pos_open) 
		{
            tmp1 = ft_strdup(str + i);
            char *tmp2 = new_str;
            new_str = ft_strjoin(new_str, tmp1);
            free(tmp1);
            free(tmp2);
            break;
        }
        quote = str[pos_open];
        pos_close = find_symb(str, quote, cr_sgm(pos_open + 1, sgm.e));
        tmp1 = ft_strndup(str + i, pos_open - i);
        char *tmp2 = new_str;
        new_str = ft_strjoin(new_str, tmp1);
        free(tmp1);
        free(tmp2);

        tmp1 = ft_strndup(str + pos_open + 1, pos_close - pos_open - 1);
        tmp2 = new_str;
        new_str = ft_strjoin(new_str, tmp1);
        free(tmp1);
        free(tmp2);

        i = pos_close + 1;
    }
    return new_str;
}

void expand_quotes(t_tree *tree)
{
	t_list *current;
	char *tmp;
	
	current = tree->list;
	while(current)
	{
		tmp = remove_outer_quotes(current->word);
		if(tmp == NULL) 
		{
			ft_printf_fd(2, "error removing outer quotes\n"); // what to do in this case?
			current = current->next;
			continue;
		}
		free(current->word);
		current->word = tmp;
		current = current->next;
		// ft_printf("%s\n", current->word);    // for testing
	}
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
	// expand_quotes(tree);
	expand_variables(tree);
	// expand_var_list(tree);
	// ft_print_list(tree->expand);
	return (0);
}
