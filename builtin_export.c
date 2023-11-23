#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* variables exported just with varname and no value dont appear in env until they get a value assigned to it.
	They appear when command export is run without arguments. so we need a separate data structure for Variables exported.
	without value. Needs to be able to export multiple variables at once. */


/* var_name is a variable in env, it returns the index of it. If not, it returns -1 */

int print_export(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(envp[i]);
		write(1, "\n", 1);
		i++;
	}
	return(0);
}

/* checks, if the variable already exists in env. If yes, it returns the index. if not it returns -1 */

int is_valid_env(char *var_name, char **envp) 
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var_name);
	while(envp[i])
	{
		if((ft_strncmp(var_name, envp[i], len) == 0) && envp[i][len] == '=')
			return(i);
		i++;
	}
	return(-1);
}

/* adds variable*/
int  add_var(char *var_name, t_data *data)
{
	int i = 0;
	char	**new_envp;

	new_envp = (char **)malloc((count_env(data->envp) + 2) * sizeof(char *));
	if(!new_envp)
		return(-1);
	while(data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]); // need to handle strdup fail
		i++;
	}
	new_envp[i] = ft_strdup(var_name);
	new_envp[i + 1] = NULL;
	free_envp(data);
	data->envp = new_envp;
	return(0);
}

/* example for command: command[0] = "export", command[1] = 'VAR_NAME=value'
	returns 0 on success, 1 on failure		  */

int builtin_export(char **command, t_data *data)
{
	int i;

	if(ft_strcmp(command[0], "export") == 0 && command[1] == NULL) // just prints env
		return(print_export(data->envp));
	i = is_valid_env(command[1], data->envp);
	if(i == -1) // need to malloc and copy envp and append variable
	{
		add_var(command[1], data);
	}
	if(i != -1)
	{
		print_export(data->envp);
	}
	return(0);
}

int main(int argc, char **argv, char **envp)
{
	char *var;
	char *command[] = {"export", "HOME", NULL};
	t_data data;

	data.envp = copy_environ(envp);
	builtin_export(command, &data);
	free_envp(&data);
	return(0);
}