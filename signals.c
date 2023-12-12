/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:16:15 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/12 14:21:25 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigint_eof(int sig) {
  (void)sig;
  g_sigint_received = 1;

  // Send EOF to the input stream
  write(STDIN_FILENO, "\x04", 1);

  // Simulate a new line to clear the input buffer
  write(STDOUT_FILENO, "\n", 1);

  // Reset the readline library state
//   rl_on_new_line();
//   rl_replace_line("", 0);
//   rl_redisplay();
}


// void	handle_sigquit(int sig)
// {
// 	(void)sig;
// 	g_sigint_received = SIGQUIT_RECEIVED;
// }
