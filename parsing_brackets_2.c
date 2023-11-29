/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_brackets_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:23 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/20 23:02:35 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	clbr(char bracket)
{
	if ('(' == bracket)
		return (')');
	if ('[' == bracket)
		return (']');
	if ('{' == bracket)
		return ('}');
	print_error(1, "in clbr not correct bracket");
	return ('\0');
}

/* in the third part of the string (after the brackets),\
we should take into account that there also could be brackets.\
So we need to call there for this exact function */
int	find_not_quoted_not_bracketed_symb(char const *str, char ch, t_sgm sgm)
{
	int		len;
	int		open_bracket_pos;
	int		pos_close;
	int		res;

	if (NULL == str || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.b > len)
		return (print_error(-1, "notquotednotbrack: error input"));
	open_bracket_pos = get_not_quoted_open_bracket_pos(str, sgm);
	if (-1 == open_bracket_pos)
		return (find_not_quoted_symb(str, ch, sgm));
	pos_close = get_pos_close(str, str[open_bracket_pos], \
				cr_sgm(open_bracket_pos, sgm.e));
	res = find_not_quoted_symb(str, ch, cr_sgm(sgm.b, open_bracket_pos));
	if (-1 != res)
		return (res);
	res = find_not_quoted_not_bracketed_symb(str, ch, \
				cr_sgm(pos_close + 1, sgm.e));
	return (res);
}

int	find_not_quoted_not_bracketed_str(char const *str, \
				char const *tkn, t_sgm sgm)
{
	int		len;
	int		open_bracket_pos;
	int		pos_close;
	int		res;

	if (NULL == str || NULL == tkn || 0 == ft_strlen(tkn) || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.b > len)
		return (print_error(-1, "notquotednotbrackstr: error input"));
	open_bracket_pos = get_not_quoted_open_bracket_pos(str, sgm);
	if (-1 == open_bracket_pos)
		return (find_not_quoted_str(str, tkn, sgm));
	pos_close = get_pos_close(str, str[open_bracket_pos], \
				cr_sgm(open_bracket_pos, sgm.e));
	res = find_not_quoted_str(str, tkn, cr_sgm(sgm.b, open_bracket_pos));
	if (-1 != res)
		return (res);
	res = find_not_quoted_not_bracketed_str(str, tkn, \
				cr_sgm(pos_close + 1, sgm.e));
	return (res);
}

int	find_not_quoted_not_bracketed_setstr(char const *str, \
				char const *const *settkn, t_sgm sgm)
{
	int		len;
	int		open_bracket_pos;
	int		pos_close;
	int		res;

	if (NULL == str || NULL == settkn || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.b > len)
		return (print_error(-1, "notquotednotbracksetstr: error input"));
	open_bracket_pos = get_not_quoted_open_bracket_pos(str, sgm);
	if (-1 == open_bracket_pos)
		return (find_not_quoted_setstr(str, settkn, sgm));
	pos_close = get_pos_close(str, str[open_bracket_pos], \
				cr_sgm(open_bracket_pos, sgm.e));
	res = find_not_quoted_setstr(str, settkn, cr_sgm(sgm.b, open_bracket_pos));
	if (-1 != res)
		return (res);
	res = find_not_quoted_not_bracketed_setstr(str, settkn, \
				cr_sgm(pos_close + 1, sgm.e));
	return (res);
}
