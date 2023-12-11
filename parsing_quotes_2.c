/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:07:47 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/16 20:12:39 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_quotes(char const *str, t_sgm sgm)
{
	int		pos_open;
	int		pos_close;
	char	quote;

	if (NULL == str || sgm.b >= sgm.e)
	{
		return (0);
		return (print_error(0, "nothing to be done in parse_quotes"));
	}
	if (sgm.b < 0 || (int)ft_strlen(str) < sgm.e)
		return (print_error(1, "wrong input in parse_quotes"));
	pos_open = get_quote_pos(str, sgm);
	if (-1 == pos_open)
		return (0);
	quote = str[pos_open];
	pos_close = find_symb(str, quote, cr_sgm(pos_open + 1, sgm.e));
	if (-1 == pos_close && '\'' == quote)
		return (print_error(2, "parsing error: quote"));
	if (-1 == pos_close && '"' == quote)
		return (print_error(2, "parsing error: dquote \""));
	return (parse_quotes(str, cr_sgm(pos_close + 1, sgm.e)));
}
