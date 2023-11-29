/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_tkns.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:15:51 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/19 22:45:08 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_list_i(t_list **list, int *i, \
		char ***tkns_arr, char const *tkns)
{
	if (NULL == list || NULL == i || NULL == tkns_arr)
		return (0);
	*list = NULL;
	*i = 0;
	*tkns_arr = ft_split(tkns, ' ');
	return (1);
}

static void	set_b_decrease_i(t_sgm *sgm, int *i)
{
	if (NULL == sgm || NULL == i)
		return ;
	sgm->b = *i;
	--(*i);
	return ;
}

t_list	*ft_split_quotes_tkns(char const *str, char const *spaces, \
				char const *tkns, char const *quotes)
{
	int		i;
	char	**tkns_arr;
	t_list	*list;
	t_sgm	sgm;

	if (NULL == str || 0 == ft_strlen(str))
		return (NULL);
	init_list_i(&list, &i, &tkns_arr, tkns);
	while ('\0' != str[i] && '\n' != str[i])
	{
		if (isin(str[i], spaces) && wc_pass_spaces(str, spaces, &i))
			continue ;
		if (0 == pass_tkn(str, (char const *const *)tkns_arr, &i, &list))
			continue ;
		set_b_decrease_i(&sgm, &i);
		while (str[++i] && 0 == isin(str[i], spaces) && \
			0 == is_str_in_setstr(&str[i], (char const *const *)tkns_arr))
			if (isin(str[i], quotes) && -1 == \
				wc_pass_quotes(str, quotes, &tkns_arr, &i))
				return (free_list_return_null(&list));
		sgm.e = i;
		ft_lstadd_back(&list, ft_lstnew(str, sgm.b, sgm.e));
	}
	wc_free_print_ft_split(&tkns_arr, 1, NULL);
	return (list);
}

int	pass_tkn(char const *str, char const *const *tkns_arr, \
					int *i, t_list **list)
{
	int		len_tkn;
	t_list	*newlistnode;

	if (NULL == str || NULL == tkns_arr || NULL == i || NULL == list)
		return (print_error(-1, "pass_tkn: NULL input"));
	len_tkn = is_str_in_setstr(&str[*i], tkns_arr);
	if (0 == len_tkn)
		return (1);
	newlistnode = ft_lstnew(str, *i, *i + len_tkn);
	newlistnode->is_special_tkn = 1;
	ft_lstadd_back(list, newlistnode);
	*i += len_tkn;
	return (0);
}

t_list	*free_list_return_null(t_list **list)
{
	ft_free_lst(list);
	return (NULL);
}
