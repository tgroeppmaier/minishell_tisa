/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_brackets_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:23 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/20 23:06:05 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	opbr(char bracket)
{
	if (')' == bracket)
		return ('(');
	if (']' == bracket)
		return ('[');
	if ('}' == bracket)
		return ('{');
	print_error(1, "in opbr not correct bracket");
	return ('\0');
}

/* in the third part of the string (after the brackets),\
we should take into account that there also could be brackets.\
So we need to call there for this exact function */
int	find_last_not_quoted_not_bracketed_symb(char const *str, char ch, t_sgm sgm)
{
	int		len;
	int		close_bracket_pos;
	int		pos_open;
	int		res;

	if (NULL == str || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.b > len)
		return (print_error(-1, "lastnotquotednotbrack: error input"));
	close_bracket_pos = get_last_not_quoted_close_bracket_pos(str, sgm);
	if (-1 == close_bracket_pos)
		return (find_last_not_quoted_symb(str, ch, sgm));
	pos_open = get_pos_open(str, str[close_bracket_pos], \
				cr_sgm(sgm.b, close_bracket_pos));
	res = find_last_not_quoted_symb(str, ch, \
				cr_sgm(close_bracket_pos + 1, sgm.e));
	if (-1 != res)
		return (res);
	res = find_last_not_quoted_not_bracketed_symb(str, ch, \
					cr_sgm(sgm.b, pos_open));
	return (res);
}

// the same thing as in previous function
int	find_last_not_quoted_not_bracketed_str(char const *str, \
				char const *tkn, t_sgm sgm)
{
	int		len;
	int		close_bracket_pos;
	int		pos_open;
	int		res;

	if (NULL == str || NULL == tkn || 0 == ft_strlen(tkn) || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.b > len)
		return (print_error(-1, "lastnotquotednotbrackstr: error input"));
	close_bracket_pos = get_last_not_quoted_close_bracket_pos(str, sgm);
	if (-1 == close_bracket_pos)
		return (find_last_not_quoted_str(str, tkn, sgm));
	pos_open = get_pos_open(str, str[close_bracket_pos], \
				cr_sgm(sgm.b, close_bracket_pos));
	res = find_last_not_quoted_str(str, tkn, cr_sgm(close_bracket_pos + 1, \
									sgm.e));
	if (-1 != res)
		return (res);
	res = find_last_not_quoted_not_bracketed_str(str, tkn, cr_sgm(sgm.b, \
								pos_open));
	return (res);
}

int	find_last_not_quoted_not_bracketed_setstr(char const *str, \
				char const *const *settkn, t_sgm sgm)
{
	int		len;
	int		close_bracket_pos;
	int		pos_open;
	int		res;

	if (NULL == str || NULL == settkn || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.b > len)
		return (print_error(-1, "lastnotquotednotbracksetstr: error input"));
	close_bracket_pos = get_last_not_quoted_close_bracket_pos(str, sgm);
	if (-1 == close_bracket_pos)
		return (find_last_not_quoted_setstr(str, settkn, sgm));
	pos_open = get_pos_open(str, str[close_bracket_pos], \
				cr_sgm(sgm.b, close_bracket_pos));
	res = find_last_not_quoted_setstr(str, settkn, \
			cr_sgm(close_bracket_pos + 1, sgm.e));
	if (-1 != res)
		return (res);
	res = find_last_not_quoted_not_bracketed_setstr(str, settkn, \
						cr_sgm(sgm.b, pos_open));
	return (res);
}
