/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:24:14 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/15 18:32:21 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_all(char const *str)
{
	if (NULL == str)
		return (1);
	if (0 != parse_quotes(str, cr_sgm(0, ft_strlen(str))) || \
		0 != parse_brackets(str, cr_sgm(0, ft_strlen(str))))
		return (1);
	return (0);
}
