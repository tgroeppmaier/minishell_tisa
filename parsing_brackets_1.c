/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_brackets_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:23 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/20 22:22:10 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_not_quoted_open_bracket_pos(char const *str, t_sgm sgm)
{
	return (find_not_quoted_setsymb(str, "([{", sgm));
}

int	doifnoopenbracket(char const *str, t_sgm sgm)
{
	int	pos_close;

	pos_close = find_not_quoted_setsymb(str, ")]}", sgm);
	if (-1 == pos_close)
		return (0);
	return (perr2(1, "parser error: closing bracket mismatch", \
					str[pos_close]));
}

// S: I forgot now why is that condition sgm.b + 2 > (int)ft_strlen(str)
// S: OK, if we get in that function, then str[sgm.b] is a bracket.
// S: but still. I replaced that with sgm.e > (int)ft_strlen(str)
int	get_pos_close(char const *str, char bracket, t_sgm sgm)
{
	int		cnt;
	int		pos_close;
	char	set[3];

	if (NULL == str || sgm.b < 0 || sgm.e > (int)ft_strlen(str))
		return (print_error(-1, "something is very wrong in get_pos_close"));
	if (str[sgm.b] != bracket)
		print_error(-2, "in get_pos_close not started with correct bracket");
	set[0] = bracket;
	set[1] = clbr(bracket);
	set[2] = '\0';
	cnt = 1;
	pos_close = sgm.b;
	while (0 != cnt)
	{
		pos_close = find_not_quoted_setsymb(str, set, \
				cr_sgm(pos_close + 1, sgm.e));
		if (-1 == pos_close)
			return (perr3(-1, "parse error: no closing br", bracket, cnt));
		if (str[pos_close] == bracket)
			++cnt;
		else if (str[pos_close] == clbr(bracket))
			--cnt;
	}
	return (pos_close);
}

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
}

int	check_in_between(char const *str, int pos_open, int pos_close, t_sgm sgm)
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
}
