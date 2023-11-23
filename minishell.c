#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "minishell.h"

int skip_whitespace(int i, char *input)
{
    char whitespace[] = " \t\r\n\v";
    
    while(input[i] && ft_strchr(whitespace, input[i]))
        i++;
    return(i);
}

void error_exit(char *str)
{
	ft_putstr(str);
	exit(1);
}

/* 	checks, if quotes of the inputs are properly closed */

bool check_closed_quotes(char *input)
{
	int i = 0;
	char quote = 'x';
	bool inquote = false;

	while(input[i])
	{
		if((input[i] == '\'' || input[i] == '"') && inquote == false)
		{
			inquote = true;
			quote = input[i];
		}
		else if((input[i] == quote) && inquote == true)
			inquote = false;
		i++;
	}
	if(inquote == true)
		return(false);
	return(true);
}

/* checks, if if the index n of input is within quotes. the start and end " or ' count as within */

bool in_quotes(int n, char *input) 
{
    int i = 0;
    char quote = '\0';
    bool inquote = false;

    while (input[i] != '\0') 
	{
        if (input[i] == '\'' || input[i] == '"') 
		{
            if (inquote == false) 
			{
                inquote = true;
                quote = input[i];
            } 
			else if (input[i] == quote) 
			{
				if (i == n) 
					return true;
                inquote = false;
                quote = '\0';
            }
        }
		if(i == n)
			return(inquote);

        
        i++;
    }
    return false;
}


// void print_tokens(char *input)
// {
// 	char *token;

// 	while(1)
// 	{
// 		token = get_next_token(input);
// 		if(token == NULL)
// 			break;
// 		// printf("token = %s\n", token);
// 	}
// }

void create_cmd_line(t_command **cmd, char *input) 
{
    int start = 0;  // Start index for each segment
    int i = 0;      // Current index in input

    while (input[i] != '\0') 
	{
        if (input[i] == '|' && !in_quotes(i, input)) {
            if (i != start) { // Ensure that the segment is non-empty
                new_cmdl_node(cmd, ft_strndup(input + start, i - start));
            }
            start = i + 1;  // Update start to the character after '|'
        }
        i++;  // Move to the next character
    }

    // Handle the last segment after the last pipe or if no pipe is present
    if (start < i) 
	{
		new_cmdl_node(cmd, ft_strndup(input + start, i - start));
    }
}

char *get_redirect(int *i, char *cmd_line)
{
	int c = 0;
	int d = 0;
	
	while(cmd_line[*i] == '<' || cmd_line[*i] == '>')
	{
		if(cmd_line[*i] == '<')
		{
			c++;
			(*i)++;
		}
		else if(cmd_line[*i] == '>')
		{
			d++;
			(*i)++;
		}
	}
	if(c == 1 && d == 0)
		return("<");
	if(c == 2 && d == 0)
		return("<<");
	if(c == 0 && d == 1)
		return(">");
	if(c == 0 && d == 2)
		return(">>");
	else
		return("error redirect\n");
}

char *get_quoted_word(int *i, char *cmd_line)
{
	int start = 0;
	char *word;
	
	start = *i;
	while(in_quotes(*i, cmd_line))
	{
		(*i)++;
	}
	word = ft_strndup(cmd_line + start, *i - start);
	return(word);
}

char *get_word(int *i, char *cmd_line)
{
	int start = 0;
	char *word;
	char whitespace[] = " \t\r\n\v";

	start = *i;

	while(cmd_line[*i] && !in_quotes(*i, cmd_line) && !ft_strchr(whitespace, cmd_line[*i]))
	{
		(*i)++;
	}
	word = ft_strndup(cmd_line + start, *i - start);
	return(word);
}

char *get_next_word(char *cmd_line)
{
    static int i = 0;
	char *token;

	while(cmd_line[i])
	{
		i = skip_whitespace(i, cmd_line);
		if (cmd_line[i] == '\0')
		{
			i = 0;
			return NULL;  // End of command line
		}
		if ((cmd_line[i] == '<' || cmd_line[i] == '>') && !in_quotes(i, cmd_line))
		{
			return(get_redirect(&i, cmd_line));
		}
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && in_quotes(i, cmd_line))
		{
			return(get_quoted_word(&i, cmd_line));
		}
		else
			return(get_word(&i, cmd_line));

		return(NULL);
	}
}

/* takes command list and generates word list, separating by whitespace and < > <<  */

void create_word_list(t_token **words, t_command *commands)
{
	int start 	= 0;
	int i 		= 0;
	char *word;

	printf("create_word_list\n");
	while(word != NULL)
	{
		word = get_next_word(commands->cmd);
		if(word != NULL)
		{
			new_word_node(words, word);
		}
		// commands = commands->next;
		// print_word_list(words);
	}
}


// char *ft_getline(t_command *cmd, char *input)
// {
// 	input = readline("\033[32mshelly $ \033[0m");
// 	if(input != NULL)
// 	{
// 		add_history(input);
// 		check_closed_quotes(input);
// 		create_cmd_line(cmd, input);
// 	}
// 	return(input);
// }

int main()
{
	char *input;
	char *token;
	char *path = getenv("PATH");
	extern char **environ;
	t_command *commands = NULL;
	// t_token		*words = NULL;
	
	while (1)
	{
		input = readline("\033[32mshelly $ \033[0m");
		if (input == NULL || ft_strcmp(input, "exit") == 0) 
		{
        	free(input);
       	 	break;
    	}
		else if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		else if(check_closed_quotes(input) == false)
		{
			ft_putstr("open quotes\n");
			free(input);
		}
		// else if(check_redirect(input) == false)
		// {
		// 	ft_putstr("invalid redirect\n");
		// 	free(input);
		// }
		else
		{
			add_history(input);
			create_cmd_line(&commands, input);
			create_word_list(&(commands->words), commands);
			print_list(commands);
			print_word_list(commands->words);
			free_cmd_list(commands);
			commands = NULL;
			free(input);
		}
	}
		rl_clear_history();
	
	return(0);
}