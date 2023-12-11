/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:16:15 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/11 13:34:29 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// void	handle_sigquit(int sig)
// {
// 	(void)sig;
// 	g_sigint_received = SIGQUIT_RECEIVED;
// }
