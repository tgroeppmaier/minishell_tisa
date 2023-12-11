/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:25:34 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/11 09:29:40 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

volatile sig_atomic_t	g_sigint_received = 0;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	(void)argv;
	if (1 != argc)
		return (print_error(1, "no arguments are allowed"));
	if (set_data(&data, envp))
		return (1);
	if (0 == READLINE_MODE)
		show_prompt(&data);
	else
		show_prompt_readline(&data);
	free_data_except_tree(&data);
	return (0);
}

/*
	//char	str[] = "ls -l -a |wc>outfile' '"; // 7
	//char	str[] = "echo \"Hello | <\" > output.txt"; // 4
	//char	str[] = "ls> out.txt"; // 3
	//char	str[] = " cat infile | wc>out.txt "; // 6
	//char	str[] = "cat infile | wc > out.txt "; // 6
	//char	str[] = "cat infile | wc > "; // 5
	//char	str[] = "\"asd \"word>>word'sd f 'word<"; // 4
	char	str[] = "cat >outfile | | \"test <>| >>'\" \f hello"; // 7
	//char	str[] = "";
	//int		words_cnt;
	t_list	*list;

	ft_printf("from main: wc is [%d]\n", cnt_words_quotes_tkns(str, \
				" \t\n\v\r\f", "<< >> < > && & || |", "\"'"));
	list = ft_split_quotes_tkns(str, " \t\n\v\r\f", \
			"<< >> < > && & || |", "\"'");
	ft_printf("from main: length is [%d]\n", ft_lstsize(list));
	ft_print_list(list);
	ft_free_lst(&list);
	//words_cnt = ft_wc(str, ' ');
	//ft_printf("[%d]\n", words_cnt);
*/
/*
	char	**cmd;
	int		i;
	char	str[3];
	
	int		dir;
	int		i;
	char	*my_dir;
	char	str[] = "\"\'\"\"\"";

	(void)argc;
	(void)argv;
	i = 4;
	ft_printf("My cool program [%d]\n", i);
	ft_printf("%s[%c]", "\033[72m", '\'');
	parse_quotes(str, 0, ft_strlen(str));
	my_dir = NULL;
	//my_dir = (char *)malloc(sizeof(char) * 100);
	my_dir = getcwd(my_dir, 100);
	ft_printf("My dir is [%s]\n", my_dir);
	dir = chdir("/");	
	my_dir = getcwd(my_dir, 100);
	ft_printf("My dir is [%s]\n", my_dir);
	sleep(4);
	ft_printf("My cool program [%d] ended\n", i);
	free(my_dir);
	show_prompt();
	ft_printf("argc = [%d]\n", argc);
	i = -1;
	while (NULL != argv[++i])
	{
		ft_printf("[%s]\n", argv[i]);
	}
	cmd = ft_split(argv[1], ' ');
	i = -1;
	while (cmd[++i] != NULL)
	{
		ft_printf("[%d]: [%s]\n", i, cmd[i]);
	}
	free_split(cmd);
	cmd = NULL;
	ft_printf("\033[H\033[J");
	while (1)
	{
		ft_printf("TISA: ");
		read(0, str, 4);
		ft_printf("\nYou entered [%s]\n", str);
		if (0 == ft_strncmp(str, "exit", 5))
			break ;
	}
	return (0);
}*/
