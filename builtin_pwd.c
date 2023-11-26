#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

char *get_env_value(char *var_name, t_data *data)
{
	int i;
	char *value;

	i = var_index(var_name, data->envp);
	if(i == -1)
		return (NULL);
	value = data->envp[i] + 4;
	return(value);
}

void builtin_pwd(t_data *data)
{
	char *pwd;
	
	pwd = get_env_value("PWD", data);
	pwd = getenv("PWD");
	if(pwd == NULL)
		printf("PWD environment variable not set");
	else
		printf("%s\n", pwd);
}