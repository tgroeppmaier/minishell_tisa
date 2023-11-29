#include "minishell.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

/* exit without arguments terminates the current process with status code 0
when the first argument is an integer, it will terminate with that status code.
when the first argument is not a valid integer (number to big/ small or invalid characters) it exits
with status code 2 and prints exit error message. if there are two or more arguments,
	it will not
exit and return status code 1*/

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

int	ft_atoi(const char *str)
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
}

void	builtin_exit(char *input, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (data->cmd->args[1] != NULL && data->cmd->args[2] != NULL)
	{
		printf("exit\nbash: exit: too many arguments\n");
		data->exit_code = 1;
		return ; // Do not exit the shell in this case
	}
	if (data->cmd->args[1] != NULL)
	{
		if (is_valid_int(data->cmd->args[1]))
			exit_code = ft_atoi(data->cmd->args[1]);
		else
		{
			printf("exit\nbash: exit: %s: numeric argument required\n",
				data->cmd->args[1]);
			exit_code = 2;
		}
	}
	free(input);
	free_data_args(data);
	free_envp(&(data->envp));
	write(1, "exit\n", 5);
	exit(exit_code);
}
