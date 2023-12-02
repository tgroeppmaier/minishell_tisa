
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_of_exec_nodes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:02:27 by Ektin Op Ur       #+#    #+#             */
/*   Updated: 2023/12/01 21:09:04 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

// void remove_outer_quotes(char *word)
// {
	
// }

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;

	str = malloc(n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}

// char	*remove_outer_quotes(char *str)
// {
// 	int		pos_open;
// 	int		pos_close;
// 	char	quote;
// 	char	*tmp1;
// 	char	*tmp2;
// 	t_sgm	sgm;
// 	char	*new_str;
// 	int 	i = 0;

// 	sgm.e = (int)ft_strlen(str);
// 	sgm.b = 0;
// 	if (sgm.e < 2 || -1 == get_quote_pos(str, sgm))
// 		return (ft_strdup(str));
// 	pos_open = get_quote_pos(str, sgm);
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
// 	new_str = ft_strdup("");
// 	while(i < sgm.e)
// 	{
// 		sgm.b = i;
// 		pos_open = get_quote_pos(str, sgm);
// 		ft_printf("open: %d\n", pos_open);
// 		if (-1 == pos_open)
// 		{
// 			tmp1 = ft_strdup(str + i);
// 			tmp2 = ft_strjoin(new_str, tmp1);
// 			free(new_str);
// 			new_str = tmp2;
// 			free(tmp1);
// 			return (new_str);
// 		}
// 		quote = str[pos_open];
// 		pos_close = find_symb(str, quote, cr_sgm(pos_open + 1, sgm.e));
// 		ft_printf("close: %d\n", pos_close);
// 		free(new_str);
// 		new_str = ft_strndup(str, pos_open);
// 		tmp1 = ft_strndup(str + pos_open + 1, pos_close - pos_open - 1);
// 		tmp2 = new_str;
// 		new_str = ft_strjoin(new_str, tmp1);
// 		free(tmp1);
// 		free(tmp2);
// 		i = pos_close + 1;
// 	}
// 	return(new_str);
// }

char *remove_outer_quotes(char *str) 
{
    int pos_open, pos_close;
    char quote;
    char *tmp1;
    t_sgm sgm;
    char *new_str = ft_strdup("");  // Initialize new_str
    int i = 0;

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
		tmp = ft_strdup(current->word);
		free(current->word);
		current->word = remove_outer_quotes(tmp);
		ft_printf("%s\n", current->word);
		current = current->next;
		free(tmp);
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
	expand_quotes(tree);
	return (0);
}