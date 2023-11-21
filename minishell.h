#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

enum type
{
    NONE, //defaut set
    ARG, //word
    FILE_IN, //word == '<'
    HERE_DOC, // word == '<<'
    FILE_OUT, //word == '>'
    FILE_OUT_SUR, //word == '>>'
    OPEN_FILE, // word following '<'
    LIMITOR, // word following '<<'
    EXIT_FILE, // word followinf '>'
    EXIT_FILE_RET // word following '>>'
};

typedef struct s_token
{
    enum type type;
    char *word;
    struct s_token *next;
}   t_token;

typedef struct s_cmd_line
{
    char				*cmd;
    t_token             *words;
    struct s_cmd_line	*next;
}	t_cmd_line;

/* 		libft.c		 */
char *ft_strchr(char *str, int c);
int ft_strlen(char *str);
void ft_putstr(char *str);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strncpy(char *dest, const char *src, int n);
char *ft_strndup(const char *str, int n);
char	**ft_split(char const *s, char c);

/* 		cmd_list.c		 */
void new_cmdl_node(t_cmd_line **node, char *cmdl);
void print_list(t_cmd_line *node);
void free_cmd_list(t_cmd_line *head);

/*      word_list.c */
void new_word_node(t_token **node, char *word);
void print_word_list(t_token *node);

#endif

