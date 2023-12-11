/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:31:25 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/05 12:35:48 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

/*S: modified 2Dec2023*/
/* exit without arguments terminates the current process
	with status code 0
when the first argument is an integer and there are no other args,
	it will terminate with that status code.
when the first argument is not a valid integer
		(number to big/ small or invalid characters)
	it exits with status code 2 and prints exit error message.
if the first argument is an integer and there are two or more arguments,
	it will not exit and return status code 1*/

bool	is_in_range(long long num)
{
	if (num >= INT_MIN && num <= INT_MAX)
		return (true);
	else
		return (false);
}

bool	is_valid_int(char *str)
{
	int			i;
	int			sign;
	long long	c;

	if (NULL == str)
		return (false);
	i = 0;
	c = 0;
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		c = c * 10 + (str[i] - '0');
		if (!is_in_range(c * sign))
			return (false);
		i++;
	}
	return (true);
}

/*int	ft_atoi(const char *str)
{
	int	c;
	int	sign;

	c = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		c = c * 10 + (*str - '0');
		str++;
	}
	return (c * sign);
}*/

// do not exit the shell in the case of exit_code 1: too many arguments
// printf("exit\nbash: exit: too many arguments\n");
/* If the first argument numeric, and nargs >= 3,
	then do not exit, exit_status 1.
   In all the other cases do exit.
   Tests to run:
	exit sdf fds   Then echo $?
	exit 34 dfs    Then echo $?
*/
int	builtin_exit(t_tree *tree)
{
	int		exit_code;

	if (NULL == tree || NULL == tree->list || NULL == tree->data)
		return (print_error(1, "NULL in builtin_exit"));
	exit_code = tree->data->exit_code;
	if (ft_lstsize(tree->list) >= 3 && is_valid_int(tree->list->next->word))
	{
		tree->data->exit_code = 1;
		write(1, "exit\n", 5);
		ft_printf_fd(2, "bash: exit: too many arguments\n");
		return (1);
	}
	if (tree->list->next != NULL)
	{
		write(1, "exit\n", 5);
		if (is_valid_int(tree->list->next->word))
			exit_code = ft_atoi(tree->list->next->word);
		else
		{
			ft_printf_fd(2, "bash: exit: %s: numeric argument required\n",
				tree->list->next->word);
			exit_code = 2;
		}
	}
	exit(do_clean_and_exit(exit_code, tree));
}
