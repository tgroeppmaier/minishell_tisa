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

int get_arg_count(char **args)
{
	int i;

	i = 0;
	while(args[i])
		i++;
	return(i);
}

void builtin_cd(t_data *data)
{
	char *path;
	// char *args[] = {path, "-l", NULL};
	// char buffer[FILENAME_MAX];
	if(get_arg_count(data->cmd->args))
	
	if(data->cmd->args[1] == NULL || ft_strcmp(data->cmd->args[1], "~") == 0)
	{
		path = ft_getenv("HOME", data);
		printf("path: %s\n", path);
		if(path == NULL)
		{
			printf("bash: cd: HOME not set\n");
			data->exit_code = 1;
			return;
		}
		if(chdir(path) == -1)
		{
			printf("bash: cd: %s: No such file or directory\n", path);
			data->exit_code = 1;
			return;
		}
	}

}
// void update_env_value(t_data *data, char *var_name, char *value) {
//     int i;
//     char *new_var;

//     i = var_index(var_name, data->envp);
//     if (i == -1) {
//         printf("var not found\n"); // needs to be corrected
//         return;
//     }

//     size_t len = strlen(var_name) + strlen(value) + 2; // +2 for '=' and '\0'
//     new_var = malloc(len);
//     if (!new_var) {
//         perror("Failed to allocate memory");
//         return;
//     }

//     snprintf(new_var, len, "%s=%s", var_name, value);
//     free(data->envp[i]);
//     data->envp[i] = new_var;
// }

// void builtin_cd(t_data *data) {
//     char buffer[FILENAME_MAX];
//     char *oldpwd = getcwd(buffer, sizeof(buffer));

//     if (data->cmd->args[1] == NULL || ft_strcmp(data->cmd->args[1], "~") == 0) {
//         if (chdir(getenv("HOME")) == -1) {
//             perror("cd");
//             data->exit_code = 1;
//             return;
//         }
//     } else {
//         if (chdir(data->cmd->args[1]) == -1) {
//             perror("cd");
//             data->exit_code = 1;
//             return;
//         }
//     }

//     // Update OLDPWD and PWD
//     if (oldpwd != NULL) {
//         update_env_value(data, "OLDPWD", oldpwd);
//     }
//     char *newpwd = getcwd(buffer, sizeof(buffer));
//     if (newpwd != NULL) {
//         update_env_value(data, "PWD", newpwd);
//     }

//     data->exit_code = 0;
// }



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