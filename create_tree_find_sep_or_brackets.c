/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_find_sep_or_brackets.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:40:25 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/23 20:04:53 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	find_sep_semicolon_pipe(char const *str, t_sgm sgm, t_node *sep)
{
	int	sep_pos;

	sep_pos = find_not_quoted_not_bracketed_symb(str, ';', sgm);
	if (-1 != sep_pos)
	{
		*sep = SEMICOLON;
		return (sep_pos);
	}
	sep_pos = find_not_quoted_not_bracketed_symb(str, '|', sgm);
	if (-1 != sep_pos && '|' != str[sep_pos + 1])
	{
		*sep = PIPE;
		return (sep_pos);
	}
	return (-1);
}*/

int	find_sep_semicolon(char const *str, t_sgm sgm, t_node *sep)
{
	int	sep_pos;

	sep_pos = find_last_not_quoted_not_bracketed_symb(str, ';', sgm);
	if (-1 != sep_pos)
	{
		*sep = SEMICOLON;
		return (sep_pos);
	}
	return (-1);
}

// not clear why not continue searching for | if first we found ||
// could it be that || is less prioritized than |, hence
// all || are already found?
// but in the latter case we do not have to do all these checks.
/* before there was a mistake, even if I did not find it experimentally.
Distinguishing between | and ||, I need the condition for str[setp_pos-1] 
only if sep_pos >= beg. Otherwise I don't have to check that.*/
int	find_sep_pipe(char const *str, t_sgm sgm, t_node *sep)
{
	int	sep_pos;

	sep_pos = find_last_not_quoted_not_bracketed_symb(str, '|', sgm);
	if (-1 != sep_pos && \
		(sep_pos == sgm.b || \
		(sep_pos > sgm.b && '|' != str[sep_pos - 1])))
	{
		*sep = PIPE;
		return (sep_pos);
	}
	return (-1);
}

// -1? if not succesfull, i.e. not correct expression, like () ()
// 1 if found bordering brackets: only this case must be subsequently treated
// 0 if did not find brackets at all
//	only_circle_brackets: 0 to treat equally all the brackets;
// in the brackets the order does not matter, because if there are more than
// one set of brackets, mistake will be thrown
int	set_brackets_pos(char const *str, t_sgm sgm, t_sgm *brackets)
{
	int	pos_open;
	int	pos_close;
	int	only_circle_brackets;

	if (NULL == str)
		return (print_error(0, "in set_brackets_pos NULL"));
	only_circle_brackets = 0;
	pos_open = get_not_quoted_open_bracket_pos(str, sgm);
	if (only_circle_brackets)
		pos_open = find_not_quoted_setsymb(str, "(", sgm);
	if (-1 == pos_open)
		return (0);
	pos_close = get_pos_close(str, str[pos_open], cr_sgm(pos_open, sgm.e));
	if (-1 == pos_close)
		return (print_error(-2, "unsanitized input in set_brackets_pos"));
	brackets->b = pos_open;
	brackets->e = pos_close;
	if (!is_str_empty(str, cr_sgm(sgm.b, pos_open)) || \
			!is_str_empty(str, cr_sgm(pos_close + 1, sgm.e)))
	{
		ft_printf_fd(STDERR_FILENO, "str:%s, %d-%d, %d, %d\n", \
			str, sgm.b, sgm.e, pos_open, pos_close);
		return (print_error(-1, "parsing error: something near brackets"));
	}
	return (1);
}
