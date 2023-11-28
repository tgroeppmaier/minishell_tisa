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
	int k;
	char *value;

	k = 0;
	i = var_index(var_name, data->envp);
	if(i == -1)
		return (NULL);
	
	while(data->envp[i][k])
	{
		if(data->envp[i][k] == '=')
			break;
		k++;
	}
	value = data->envp[i] + k + 1;
	return(value);
}

void builtin_pwd(t_data *data)
{
	char *pwd;
	
	pwd = ft_getenv("PWD", data);
	if(pwd == NULL)
	{
		printf("PWD environment variable not set\n");
		data->exit_code = 1;
	}
	else
	{
		printf("%s\n", pwd);
		data->exit_code = 0;
	}
}