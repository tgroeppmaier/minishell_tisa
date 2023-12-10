/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:16:15 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/10 22:14:45 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	sigint_received = 1;
	write(STDOUT_FILENO, "\n", 1); // Safely write a newline character
	rl_on_new_line();              // Prepare readline to handle the new line
	rl_replace_line("", 0);        // Clear the current line
	rl_redisplay();                // Redisplay the prompt
}

void	handle_sigquit(int sig)
{
	(void)sig;
	sigint_received = SIGQUIT_RECEIVED;
	write(1, "Quit (core dumped)\n", 19);
	exit(EXIT_FAILURE); // Or handle as required
}

		// if (sigint_received == SIGQUIT_RECEIVED)
		// {
		// }
