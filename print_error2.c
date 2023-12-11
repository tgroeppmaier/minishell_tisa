/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 22:27:52 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/08 16:03:39 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This is a nonsense and should be redone */
int	print_err_empty_str_in_cmd(int res, char const *cmd)
{
	if (NULL == cmd || 0 == is_str_empty(cmd, cr_sgm(0, ft_strlen(cmd))))
		return (print_error(res, "wrong call to print_err_empty_str_in_cmd"));
	if (0 == ft_strlen(cmd))
		return (print_error(res, "Command '' is not found"));
	ft_printf_fd(STDERR_FILENO, "%s[%s]: command not found%s\n", \
						BUFF_RED, cmd, RES);
	return (res);
}
