/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_brackets_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:23 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/20 22:23:48 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_not_quoted_close_bracket_pos(char const *str, t_sgm sgm)
{
	return (find_last_not_quoted_setsymb(str, ")]}", sgm));
}

int	doifnoclosebracket(char const *str, t_sgm sgm)
{
	int	pos_open;

	pos_open = find_last_not_quoted_setsymb(str, "([{", sgm);
	if (-1 == pos_open)
		return (0);
	return (perr2(1, "parser error: opening bracket mismatch", \
					str[pos_open]));
}

// S: I forgot now why is that condition sgm.b + 2 > (int)ft_strlen(str)
// S: OK, if we get in that function, then str[sgm.b] is a bracket.
// S: but still. I replaced that with sgm.e > (int)ft_strlen(str)
int	get_pos_open(char const *str, char bracket, t_sgm sgm)
{
	int		cnt;
	int		pos_open;
	char	set[3];

	if (NULL == str || sgm.b < 0 || sgm.e > (int)ft_strlen(str))
		return (print_error(-1, "something is very wrong in get_pos_open"));
	if (str[sgm.e] != bracket)
		print_error(-2, "in get_pos_open not ended with correct bracket");
	set[0] = bracket;
	set[1] = opbr(bracket);
	set[2] = '\0';
	cnt = 1;
	pos_open = sgm.e;
	while (0 != cnt)
	{
		pos_open = find_last_not_quoted_setsymb(str, set, \
				cr_sgm(sgm.b, pos_open));
		if (-1 == pos_open)
			return (perr3(-1, "parse error: no opening br", bracket, cnt));
		if (str[pos_open] == bracket)
			++cnt;
		else if (str[pos_open] == opbr(bracket))
			--cnt;
	}
	return (pos_open);
}

/* I did not rewrite these functions to traverse backward because
   I don't think that need this
int	parse_brackets(char const *str, t_sgm sgm)
{
	int		pos_open;
	int		pos_close;
	char	bracket;

	if (NULL == str || sgm.b < 0 || sgm.e > (int)ft_strlen(str))
		return (print_error(1, "wrong input in parse_brackets"));
	if (sgm.b >= sgm.e)
		return (0);
	pos_open = get_not_quoted_open_bracket_pos(str, sgm);
	if (-1 == pos_open)
		return (doifnoopenbracket(str, sgm));
	bracket = str[pos_open];
	pos_close = get_pos_close(str, bracket, cr_sgm(pos_open, sgm.e));
	if (-1 == pos_close)
		return (1);
	return (check_in_between(str, pos_open, pos_close, sgm));
}*/

/*int	check_in_between(char const *str, int pos_open, int pos_close, t_sgm sgm)
{
	int	res;

	if (NULL == str)
		return (print_error(2, "check_in_between: cannot happen"));
	res = parse_brackets(str, cr_sgm(sgm.b, pos_open));
	if (res)
		return (res);
	res = parse_brackets(str, cr_sgm(pos_open + 1, pos_close));
	if (res)
		return (res);
	res = parse_brackets(str, cr_sgm(pos_close + 1, sgm.e));
	if (res)
		return (res);
	return (0);
}*/
