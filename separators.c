/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:33:50 by aminakov          #+#    #+#             */
/*   Updated: 2023/11/16 19:35:17 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_sep(int sep)
{
	if (SEMICOLON == sep)
		return (1);
	if (PIPE == sep)
		return (1);
	if (ANDAND == sep || OROR == sep)
		return (2);
	return (-1);
}
