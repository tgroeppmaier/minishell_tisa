#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

/* exit without arguments terminates the current process with status code 0
when the first argument is an integer, it will terminate with that status code.
when the first argument is not a valid integer (number to big/ small or invalid characters) it exits
with status code 2 and prints exit + error message*/

bool is_in_range(long long num)
{
	if(num >= INT_MIN && num <= INT_MAX)
		return(true);
	else
		return(false);
}

/* 	i = 0	c = 0	sign = 1 */

bool is_valid_int(int i, long long c, int sign, char *str)
{
	if (str[0] == '-')
		sign = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if(!str[i])
		return(false);
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return(false);
		i++;
	}
	i = 0;
	if(str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		c = c * 10 + (str[i] - '0');
		if(!is_in_range(c * sign))
			return(false);
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
	if (ft_strcmp(data->cmd->args[0], "exit") == 0 && data->cmd->args[1] == NULL)
	{
		free_data_args(data);
		free(input);
		free_envp(&(data->envp));
		exit(0);
	}
	if (data->cmd->args[2] != NULL) // does not exit
	{
		printf("exit\nbash: exit: too many arguments\n");
		data->exit_code = 1;
		return ;
	}
	if (is_valid_int(0, 0, 1, data->cmd->args[1]))
	{
		free(input);
		exit(ft_atoi(data->cmd->args[1]));
	}
	else
	{
		printf("exit\nbash: exit: %s: numeric argument required\n",
			data->cmd->args[1]);
		free_data_args(data);
		free(input);
		free_envp(&(data->envp));
		exit(2);
	}
}
