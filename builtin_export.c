#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* variables exported just with varname and no value dont appear in env until they get a value assigned to it. */


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

char  **add_var(char *var_name, char **envp)
{
	int i = 0;
	char	**new_envp;

	new_envp = malloc((count_env(envp) + 2) * sizeof(char *));
	if(!new_envp)
		return(NULL);
	while(envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(var_name);
	new_envp[i + 1] = NULL;
	free_envp(envp);
	return(new_envp);
}

/* example for command: command[0] = "export", command[1] = 'VAR_NAME="value"'  */

int builtin_export(char **command, char **envp)
{
	int i;

	if(ft_strcmp(command[0], "export") == 0 && command[1] == NULL)
		return(print_export(envp));
	i = is_valid_env(command[1], envp);
	if(i == -1) // need to malloc and copy envp and append variable
	{
		add_var(command[1], envp);
	}

	return(0);
}

int main(int argc, char **argv, char **envp)
{
	char *var;
	char *args[] = {"export", NULL};
	char **new_envp;

	// printf("env test: %s\n", envp[36]);
	new_envp = copy_environ(envp);
	builtin_export(args, envp);
	// envp[36] = ft_strdup("TEST=test");
	// printf("env test: %s\n", new_envp[36]);
	free_envp(new_envp);
	// execve(args[0], args, envp);
	return(0);
}