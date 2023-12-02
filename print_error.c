/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:13:07 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/20 12:06:01 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(int res, char const *str)
{
	if (NULL == str || ft_strlen(str) == 0)
		return (res);
	if (0 == res)
		ft_printf_fd(STDERR_FILENO, "%s", BUFF_GREEN);
	else
		ft_printf_fd(STDERR_FILENO, "%s", BUFF_RED);
	ft_printf_fd(STDERR_FILENO, "[%s]%s\n", str, RES);
	return (res);
}

int	perr2(int res, char const *str, char ch)
{
	if (NULL == str || ft_strlen(str) == 0)
		return (res);
	if (0 == res)
		ft_printf_fd(STDERR_FILENO, "%s", BUFF_GREEN);
	else
		ft_printf_fd(STDERR_FILENO, "%s", BUFF_RED);
	ft_printf_fd(STDERR_FILENO, "[%s: \'%c\']%s\n", str, ch, RES);
	return (res);
}

int	perr3(int res, char const *str, char ch, int num)
{
	if (NULL == str || ft_strlen(str) == 0)
		return (res);
	if (0 == res)
		ft_printf_fd(STDERR_FILENO, "%s", BUFF_GREEN);
	else
		ft_printf_fd(STDERR_FILENO, "%s", BUFF_RED);
	ft_printf_fd(STDERR_FILENO, "[%s: \'%c\', %d]%s\n", str, ch, num, RES);
	return (res);
}

int	print_error_grammar(int res, t_node node)
{
	if (PIPE == node)
		return (print_error(res, "pipe grammar problem"));
	if (ANDAND == node)
		return (print_error(res, "&& grammar problem"));
	if (OROR == node)
		return (print_error(res, "|| grammar problem"));
	return (print_error(res, "unexpected usage of print_error_grammar"));
}

int	print_error_syntax(int res, t_list *list)
{
	if (NULL != list)
		ft_printf_fd(STDERR_FILENO, "%ssyntax error near %s%s\n", \
			BUFF_RED, list->word, RES);
	return (res);
}
