/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_file_descriptors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:27:05 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/09 18:39:09 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set FD_CLOEXEC file on sgm.b, man dup fcntl(2)
// set FD_CLOEXEC file on sgm.e
/* we actually do copy only if the command is builtin.
Otherwise there is some problem in case of cmd1|cmd2:
part of the red color is printed when error message is printed  */
int	make_a_copy_of_fd(t_sgm *sgm, t_tree *tree)
{
	if (!sgm)
		return (print_error(1, "NULL in  make_a_copy"));
	if (!tree)
		return (0);
	sgm->b = dup(STDIN_FILENO);
	sgm->e = dup(STDOUT_FILENO);
	return (0);
}

int	restore_file_descriptors_close_copies(t_sgm sgm, t_tree *tree)
{
	if (!tree)
		return (0);
	dup2(sgm.b, STDIN_FILENO);
	close(sgm.b);
	dup2(sgm.e, STDOUT_FILENO);
	close(sgm.e);
	return (0);
}
