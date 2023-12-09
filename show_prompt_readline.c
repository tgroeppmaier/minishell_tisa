/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_prompt_readline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:10:04 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/09 13:47:39 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_base_msg_tree_bene(char *base_msg, int size, t_tree **tree,
		int *bene)
{
	char	*char_ptr;

	ft_strlcpy(base_msg, OPTGREEN, size);
	ft_strlcat(base_msg, "[", size);
	char_ptr = ft_itoa(getpid());
	ft_strlcat(base_msg, char_ptr, size);
	do_free_str(&char_ptr);
	ft_strlcat(base_msg, "]", size);
	ft_strlcat(base_msg, SHELL_NAME, size);
	if (NULL != tree)
		*tree = NULL;
	if (NULL != bene)
		*bene = 1;
}

// edge is 3 for printing number of the command
int	set_welcome_msg(char *welcome_msg, int size, int num)
{
	char	*char_ptr;
	int		len_num;
	char	last_symbs_of_shell_names[64];
	int		pos;

	if (NULL == welcome_msg)
		return (print_error(1, "NULL msg in set_welcome_msg"));
	ft_strlcpy(last_symbs_of_shell_names, "a", 64);
	pos = find_last_setsymb(welcome_msg, last_symbs_of_shell_names, cr_sgm(0,
				ft_strlen(welcome_msg)));
	if (-1 == pos)
		return (print_error(2, "wrong msg in set_welcome_msg"));
	welcome_msg[pos + 1] = '\0';
	char_ptr = ft_itoa(num);
	len_num = ft_strlen(char_ptr);
	if (1 == len_num)
		ft_strlcat(welcome_msg, "  ", size);
	else if (2 == len_num)
		ft_strlcat(welcome_msg, " ", size);
	ft_strlcat(welcome_msg, char_ptr, size);
	do_free_str(&char_ptr);
	ft_strlcat(welcome_msg, "$ ", size);
	ft_strlcat(welcome_msg, OPTWHITE, size);
	return (0);
}

int	show_prompt_readline(t_data *data)
{
	char	*str;
	t_tree	*tree;
	int		bene;
	char	welcome_msg[100];

	set_base_msg_tree_bene(welcome_msg, sizeof(welcome_msg), &tree, &bene);
	while (bene++)
	{
		if (sigint_received)
			sigint_received = 0;
		set_welcome_msg(welcome_msg, sizeof(welcome_msg), bene - 1);
		str = readline(welcome_msg);
		if (str == NULL)
		{
			if (sigint_received)
				continue ; // Signal was received, loop again
			break ; // Otherwise, NULL str means EOF, exit the loop
		}
		if (0 != parse_all(str) && 1 == do_free_str(&str))
			continue ;
		if (0 == is_str_empty(str, cr_sgm(0, ft_strlen(str))))
			add_history(str);
		if (DEBUG_MODE)
			ft_printf("You entered [%s]\n", str);
		create_display_free_tree(&tree, str, 1 + 2 * DEBUG_MODE, data);
		if (0 == ft_strncmp(str, "exit", ft_strlen(str) + 1))
			bene = 0;
		else
			ft_execute_tree(tree);
		free_tree(&tree);
		do_free_str(&str);
	}
	return (clear_history_return_zero());
}

int	clear_history_return_zero(void)
{
	clear_history();
	return (0);
}
