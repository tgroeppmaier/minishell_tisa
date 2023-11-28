#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

void	exec_int_function(char *input, t_data *data)
{
	if(ft_strcmp(data->cmd->args[0], "exit") == 0)
		builtin_exit(input, data);
	if (ft_strcmp(data->cmd->args[0], "export") == 0)
		data->exit_code = builtin_export(data->cmd->args, data);
	if(ft_strcmp(data->cmd->args[0], "env") == 0)
	{
		if(data->cmd->args[1] == NULL)
			builtin_env(data->envp, data);
		else
		{
			printf("env: '%s': No such file or directory\n", data->cmd->args[1]); // needs to be replaced with ft_printf
			data->exit_code = 127;
		}
		return ;
	}
	if(ft_strcmp(data->cmd->args[0], "echo") == 0)
		data->exit_code = builtin_echo(data->cmd->args);
	if(ft_strcmp(data->cmd->args[0], "pwd") == 0)
		data->exit_code = builtin_pwd(data);
	if(ft_strcmp(data->cmd->args[0], "cd") == 0)
		data->exit_code = builtin_cd(data);
	if(ft_strcmp(data->cmd->args[0], "unset") == 0)
		data->exit_code = builtin_unset(data);
}

/*  main is only for testing the internal commands. when testing,
	the first word must always be the internal command. because if its not ,
	the builtin_export	function would not have been called in the first place */

// int	main(int argc, char **argv, char **envp)
int main()
{
	char		*input;
	t_data		data;
	t_command	cmd;
	extern char **environ;

	data.envp = copy_environ(environ, 0);
	data.cmd = &cmd;
	while (1)
	{
		input = readline("run_built_in_commands $ ");
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		data.cmd->args = ft_split(input, ' ');
		exec_int_function(input, &data);
		free_data_args(&data);
		free(input);
	}
	print_export(data.envp);
	clear_history();
	free_envp(&(data.envp));
	return (0);
}
