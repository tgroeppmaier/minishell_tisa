#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

char *ft_getenv(char *var_name, t_data *data)
{
	int i;
	char *value;

	i = var_index(var_name, data->envp);
	if(i == -1)
		return (NULL);
	value = data->envp[i] + 5;
	return(value);
}

void builtin_pwd(t_data *data)
{
	char *pwd;
	
	pwd = ft_getenv("PWD", data);
	if(pwd == NULL)
	{
		printf("PWD environment variable not set");
		data->exit_code = 1;
	}
	else
	{
		printf("%s\n", pwd);
		data->exit_code = 0;
	}
}