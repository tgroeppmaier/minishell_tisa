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
	char *cmd;   // the command line until pipe
	char **args; // this should be the splitted command line into words after expansion and remove of quotes
	t_token				*words;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				*user_input; // the whole command line
	char				**envp;
	char				*working_dir;
	char				*old_working_dir;
	int					exit_code;  // last command exit code
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
bool					ft_isalpha(int c);
bool					ft_isdigit(int c);
char	*ft_strjoin(char const *s1, char const *s2);

/* 		cmd_list.c			*/
void					new_cmdl_node(t_command **node, char *cmdl);
void					print_list(t_command *node);
void					free_cmd_list(t_command *head);

/*      word_list.c */
void					new_word_node(t_token **node, char *word);
void					print_word_list(t_token *node);

/* 		builtin_echo */
int						builtin_echo(char **words);

/*      builtin_env */
char					**copy_environ(char **envp, int additional_space);
void					free_envp(char ***envp);
int 					builtin_env(t_data *data);
int						count_env(char **envp);

/* 		builtin_export */
int						builtin_export(char **args, t_data *data);
void					free_data_args(t_data *data);
int					print_export(char **envp);
int	var_index(char *var_name, char **envp);
bool	is_valid_name(char *var_name);
void update_var(char *var_name, t_data *data);
void update_var(char *var_name, t_data *data);
bool	does_var_exist(char *var_name, char **envp);
void add_var(char *var_name, t_data *data);


/* 		builtin_exit */
void builtin_exit(char *input, t_data *data);

/* 		builtin_pwd  */
int builtin_pwd(t_data *data);
char *ft_getenv(char *var_name, t_data *data);

/* 		builtin_cd */
int builtin_cd(t_data *data);

/* 		builtin_unset */
int builtin_unset(t_data *data);

#endif
