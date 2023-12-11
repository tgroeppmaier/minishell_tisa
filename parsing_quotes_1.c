/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:07:47 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/20 21:13:42 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_pos(char const *str, t_sgm sgm)
{
	return (find_setsymb(str, "'\"", sgm));
}

int	find_not_quoted_symb(char const *str, char ch, t_sgm sgm)
{
	char	quote;
	int		open_quote_pos;
	int		close_quote_pos;
	int		symb_pos;
	int		len;

	if (NULL == str || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.e > len)
		return (print_error(-2, "find_not_quoted_symb: error input"));
	open_quote_pos = get_quote_pos(str, sgm);
	if (-1 == open_quote_pos)
		return (find_symb(str, ch, sgm));
	quote = str[open_quote_pos];
	symb_pos = find_symb(str, ch, cr_sgm(sgm.b, open_quote_pos));
	if (-1 != symb_pos)
		return (symb_pos);
	close_quote_pos = find_symb(str, quote, cr_sgm(open_quote_pos + 1, sgm.e));
	if (-1 == close_quote_pos)
		print_error(-3, "in find_not_quoted_symb: not sanitized input");
	return (find_not_quoted_symb(str, ch, cr_sgm(close_quote_pos + 1, sgm.e)));
}

int	find_not_quoted_setsymb(char const *str, char *set, t_sgm sgm)
{
	char	quote;
	int		open_quote_pos;
	int		close_quote_pos;
	int		symb_pos;
	int		len;

	if (NULL == str || NULL == set || 0 == ft_strlen(set) || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.e > len)
		return (print_error(-2, "find_not_quoted_setsymb: error input"));
	open_quote_pos = get_quote_pos(str, sgm);
	if (-1 == open_quote_pos)
		return (find_setsymb(str, set, sgm));
	quote = str[open_quote_pos];
	symb_pos = find_setsymb(str, set, cr_sgm(sgm.b, open_quote_pos));
	if (-1 != symb_pos)
		return (symb_pos);
	close_quote_pos = find_symb(str, quote, cr_sgm(open_quote_pos + 1, sgm.e));
	if (-1 == close_quote_pos)
		print_error(-3, "in find_not_quoted_setsymb: not sanitized input");
	return (find_not_quoted_setsymb(str, set, \
		cr_sgm(close_quote_pos + 1, sgm.e)));
}

int	find_not_quoted_str(char const *str, char const *tkn, t_sgm sgm)
{
	char	quote;
	int		open_quote_pos;
	int		close_quote_pos;
	int		tkn_pos;
	int		len;

	if (NULL == str || NULL == tkn || 0 == ft_strlen(tkn) || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.e > len)
		return (print_error(-2, "find_not_quoted_str: error input"));
	open_quote_pos = get_quote_pos(str, sgm);
	if (-1 == open_quote_pos)
		return (find_str(str, tkn, sgm));
	quote = str[open_quote_pos];
	tkn_pos = find_str(str, tkn, cr_sgm(sgm.b, open_quote_pos));
	if (-1 != tkn_pos)
		return (tkn_pos);
	close_quote_pos = find_symb(str, quote, cr_sgm(open_quote_pos + 1, sgm.e));
	if (-1 == close_quote_pos)
		print_error(-3, "in find_not_quoted_str: not sanitized input");
	return (find_not_quoted_str(str, tkn, cr_sgm(close_quote_pos + 1, sgm.e)));
}

int	find_not_quoted_setstr(char const *str, \
		char const *const *settkn, t_sgm sgm)
{
	char	quote;
	int		open_quote_pos;
	int		close_quote_pos;
	int		tkn_pos;
	int		len;

	if (NULL == str || NULL == settkn || sgm.b >= sgm.e)
		return (-1);
	len = ft_strlen(str);
	if (sgm.b < 0 || sgm.e > len)
		return (print_error(-2, "find_not_quoted_setstr: error input"));
	open_quote_pos = get_quote_pos(str, sgm);
	if (-1 == open_quote_pos)
		return (find_setstr(str, settkn, sgm));
	quote = str[open_quote_pos];
	tkn_pos = find_setstr(str, settkn, cr_sgm(sgm.b, open_quote_pos));
	if (-1 != tkn_pos)
		return (tkn_pos);
	close_quote_pos = find_symb(str, quote, cr_sgm(open_quote_pos + 1, sgm.e));
	if (-1 == close_quote_pos)
		print_error(-3, "in find_not_quoted_setstr: not sanitized input");
	return (find_not_quoted_setstr(str, settkn, \
		cr_sgm(close_quote_pos + 1, sgm.e)));
}
