#include "minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>


void update_env_value(t_data *data, char *var_name, char *value)
{
	int i;
	char *new;

	i = var_index(var_name, data->envp);
	if(i == -1)
	{
		printf("var not found\n"); // needs to be corrected
		return;
	}
	free(data->envp[i]);
	new = ft_strjoin(var_name, value);
	data->envp[i] = new;
}

void builtin_cd(t_data *data)
{
	// char *path = "/usr/bin/ls";
	// char *args[] = {path, "-l", NULL};
	char buffer[FILENAME_MAX];
	// char *new_value;

	if(data->cmd->args[1] == NULL || ft_strcmp(data->cmd->args[1], "~") == 0)
	{
		if(chdir(getenv("HOME")) == -1)
		{
			perror("cd");
			data->exit_code = 1;
		}
		update_env_value(data, "OLDPWD", getenv("PWD"));
		printf("%s\n", getcwd(buffer, sizeof(buffer)));
		// printf("%s\n", getenv("PWD"));
	}
}

// void free_all(char **words)
// {
// 	int i = 0;
	
// 	while(words[i])
// 	{
// 		free(words[i]);
// 		i++;
// 	}
// 	free(words);
// }

// int	main(void)
// {
// 	char *input;
// 	char **words;
// 	extern char **environ;

// 	printf("envp count: %d\n",count_envp(environ));
// 	free_envp(environ);
// 	printf("envp count: %d\n",count_envp(environ));

// 	while (1)
// 	{
// 		input = readline("built_ins $ ");
// 		if (ft_strcmp(input, "exit") == 0)
// 		{
// 			free(input);
// 			break ;
// 		}
// 		else if (input[0] == '\0')
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		words = ft_split(input, ' ');
// 		builtin_cd(words);
// 		add_history(input);
// 		// free_all(words);
// 	}
// 	return (0);
// }