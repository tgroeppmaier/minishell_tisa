#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

enum					type
{
	NONE,         // defaut set
	ARG,          // word
	FILE_IN,      // word == '<'
	HERE_DOC,     // word == '<<'
	FILE_OUT,     // word == '>'
	FILE_OUT_SUR, // word == '>>'
	OPEN_FILE,    // word following '<'
	LIMITOR,      // word following '<<'
	EXIT_FILE,    // word followinf '>'
	EXIT_FILE_RET // word following '>>'
};

typedef struct s_token
{
	enum type			type;
	char				*word;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				*cmd;   // the whole command line until pipe
	char				**args; // this should be the splitted command line into words after expansion and remove of quotes
	t_token				*words;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				*user_input;
	char				**envp;
	char				*working_dir;
	char				*old_working_dir;
	int					exit_code;
	t_command			*cmd;
	pid_t				pid;
}						t_data;

/* 		libft.c			*/
char					*ft_strchr(char *str, int c);
int						ft_strlen(char *str);
void					ft_putstr(char *str);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					**ft_split(char const *s, char c);
char					*ft_strncpy(char *dest, const char *src, int n);
char					*ft_strdup(const char *s1);
char					*ft_strndup(const char *s1, size_t n);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
bool ft_isalpha(int c);
bool ft_isdigit(int c);
/* 		cmd_list.c			*/
void					new_cmdl_node(t_command **node, char *cmdl);
void					print_list(t_command *node);
void					free_cmd_list(t_command *head);

/*      word_list.c */
void					new_word_node(t_token **node, char *word);
void					print_word_list(t_token *node);

/*      builtin_env */
char					**copy_environ(char **envp);
int	free_envp(t_data *data);
int	count_env(char **envp);

#endif
