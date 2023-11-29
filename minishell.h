/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:49:23 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/11/29 18:05:20 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h> // waitpid(-1, NULL, 0);
# include <errno.h> // for while (wait(NULL!=-1||errno!=ECHILD))
# include <fcntl.h> // open, O_RDONLY, O_WRONLY

/* do not use the combination GREEN RES, instead use GREEN WHITE, 
because in the first case pressing TAB and then backslash allows 
to enter last printed character
just GREEN with TAB + BACKSLASH allows to enter several printed charachters
*/

//# define RES "\001\033[0m\002"
# define RES "\033[0m"
# define BLINKING "\033[5m"
# define RED "\033[31m"
# define BUFF_RED "\033[41m"
# define GREEN "\001\033[32m\002"
# define BUFF_GREEN "\033[42m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define LBL "\033[36m"
# define GREY "\033[37m"
# define WHITE "\033[39m"

// -D DEBUG_MODE=1 : for debug; for performance, 0

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

/* BUGS:
	- for tabs or spaces returns an error
	- does not free space for Ctrl+C, Ctrl+\.
	  Surprisingly, it works for Ctrl+D. But maybe not as expected?
	  Yes, not as expected.
	- copying and pasting into tisa minishell makes it directly executed.
	  copying without newline works. But the normal shell does not do it
	  anyway.
*/

typedef struct s_interval
{
	int	b;
	int	e;
}	t_sgm;

typedef enum e_node {SEMICOLON, PIPE, ANDAND, OROR, BRACKETS, \
			IN, ININ, OUT, OUTOUT, EXEC}	t_node;

typedef struct s_tree
{
	char			*cmd;
	struct s_tree	*left_child;
	struct s_tree	*right_child;
	struct s_tree	*head;
	t_list			*list;
	char			**envp;
	int				beg;
	int				end;
	int				level;
	int				bene;
	int				do_in_child_process;
	t_node			node;
}	t_tree;

// print_error.c
int		print_error(int res, char const *str);
int		perr2(int res, char const *str, char ch);
int		perr3(int res, char const *str, char ch, int num);
int		print_error_grammar(int res, t_node node);
int		print_error_syntax(int res, t_list *list);

// parsing.c
int		parse_all(char const *str);

// segment.c
t_sgm	cr_sgm(int beg, int end);

// PARSING
//////////////////////////////////////////////
//--------------------------------------------------------
// parsing_aux_find_symb.c
int		find_symb(char const *str, char ch, t_sgm sgm);
int		isin(char ch, char const *set);
int		find_setsymb(char const *str, char const *set, t_sgm sgm);

// last_parsing_aux_find_symb.c
int		find_last_symb(char const *str, char ch, t_sgm sgm);
int		find_last_setsymb(char const *str, char const *set, t_sgm sgm);

//--------------------------------------------------------
// parsing_aux_find_str.c
int		find_str(char const *str, char const *tkn, t_sgm sgm);
int		is_str_in_setstr(char const *str, char const *const *setstr);
int		find_setstr(char const *str, char const *const *settkn, t_sgm sgm);

// last_parsing_aux_find_str.c
int		find_last_str(char const *str, char const *tkn, t_sgm sgm);
int		is_end_of_str_in_setstr(char const *str, t_sgm sgm, \
						char const *const *setstr);
int		find_last_setstr(char const *str, char const *const *settkn, t_sgm sgm);

//--------------------------------------------------------
// parsing_quotes_1.c
int		get_quote_pos(char const *str, t_sgm sgm);
int		find_not_quoted_symb(char const *str, char ch, t_sgm sgm);
int		find_not_quoted_setsymb(char const *str, char *set, t_sgm sgm);
int		find_not_quoted_str(char const *str, char const *tok, t_sgm sgm);
int		find_not_quoted_setstr(char const *str, \
					char const *const *tok, t_sgm sgm);

// last_parsing_quotes_1.c -1 for not found; -1, -2 for errors
int		get_last_quote_pos(char const *str, t_sgm sgm);
int		find_last_not_quoted_symb(char const *str, char ch, t_sgm sgm);
int		find_last_not_quoted_setsymb(char const *str, char *set, t_sgm sgm);
int		find_last_not_quoted_str(char const *str, char const *tok, t_sgm sgm);
int		find_last_not_quoted_setstr(char const *str, \
					char const *const *tok, t_sgm sgm);

//--------------------------------------------------------
// parsing_quotes_2.c
int		parse_quotes(char const *str, t_sgm sgm);

//--------------------------------------------------------
// parsing_brackets_1.c
int		get_not_quoted_open_bracket_pos(char const *str, t_sgm sgm);
int		doifnoopenbracket(char const *str, t_sgm sgm);
int		get_pos_close(char const *str, char bracket, t_sgm sgm);
int		parse_brackets(char const *str, t_sgm sgm);
int		check_in_between(char const *str, int posop, int poscl, t_sgm smg);

// last_parsing_brackets_1.c
int		get_last_not_quoted_close_bracket_pos(char const *str, t_sgm sgm);
int		doifnoclosebracket(char const *str, t_sgm sgm);
int		get_pos_open(char const *str, char bracket, t_sgm sgm);

//--------------------------------------------------------
// parsing_brackets_2.c
char	clbr(char bracket);
int		find_not_quoted_not_bracketed_symb(char const *str, char c, t_sgm s);
int		find_not_quoted_not_bracketed_str(char const *str, \
					char const *tkn, t_sgm s);
int		find_not_quoted_not_bracketed_setstr(char const *str, \
					char const *const *settkn, t_sgm s);

// last_parsing_brackets_2.c
char	opbr(char bracket);
int		find_last_not_quoted_not_bracketed_symb(char const *str, \
							char c, t_sgm s);
int		find_last_not_quoted_not_bracketed_str(char const *str, \
					char const *tkn, t_sgm s);
int		find_last_not_quoted_not_bracketed_setstr(char const *str, \
					char const *const *settkn, t_sgm s);

// PROGRRAM ITSELF
//////////////////////////////////////////////
// show_prompt.c
void	trim_last_nl(char *str);
int		show_prompt(char *envp[]);
int		do_free_str(char **str);

// CREATION OF THE TREE
//////////////////////////////////////////////
//--------------------------------------------------------
// create_tree.c
int		create_tree(t_tree **tree, char *str, t_sgm sgm, char *envp[]);
int		do_if_sep(t_tree *tree, int sep_pos, t_node sep);
int		doifbrackets_in_create_tree(t_tree *tree, t_sgm brackets);
int		set_separate_pos(char const *str, t_sgm sgm, t_node *sep);
int		check_input_str_sgm(char const *str, t_sgm sgm);

// create_tree_aux.c
void	prefill_node(t_tree *tree, char *str, t_sgm sgm, char *envp[]);
void	free_tree(t_tree **tree);
void	print_tree(t_tree *tree);
void	create_display_free_tree(t_tree **tree, char *str, int mode, \
							char *envp[]);

// create_tree_find_sep_or_brackets.c
int		find_sep_semicolon(char const *str, t_sgm sgm, t_node *sep);
int		find_sep_pipe(char const *str, t_sgm sgm, t_node *sep);
int		set_brackets_pos(char const *str, t_sgm sgm, t_sgm *brackets);

// create_tree_post_processing1.c
int		is_str_empty(char const *str, t_sgm sgm);
void	set_levels_and_head(t_tree *tree);
void	retrieve_bene(t_tree *tree);
int		is_tree_empty(t_tree *tree);
int		does_grammar_have_mistakes(t_tree *tree);

// create_tree_pos_processing2.c
int		does_list_have_mistakes(t_list *list);
int		do_exec_nodes_have_mistakes(t_tree *tree);

// processing_of_exec_nodes.c
int		expand_exec_nodes(t_tree *tree);

// separators.c
int		len_sep(int sep);

// EXPANSION OF THE LAST NODES INTO LINKED LIST
//////////////////////////////////////////////
//--------------------------------------------------------
// wc_quotes_tkns.c
int		cnt_words_quotes_tkns(char const *str, char const *spaces, \
			char const *tkns, char const *quotes);
int		wc_pass_spaces(char const *str, char const *spaces, int *i);
int		wc_pass_tkn(char const *str, char const *const *tkns_arr, \
							int *i, int *wc);
int		wc_pass_quotes(char const *str, char const *quotes, \
					char ***tkns_arr, int *i);
int		wc_free_print_ft_split(char ***tkns_arr, int res, char const *msg);

// ft_split_quotes_tkns.c
/*static int	init_list_i(t_list **list, int *i, char ***tkns_arr, \
						char const *tkns);*/
//static void	set_b_decrease_i(t_sgm *sgm, int *i);
t_list	*ft_split_quotes_tkns(char const *str, char const *spaces, \
			char const *tkns, char const *quotes);
int		pass_tkn(char const *str, char const *const *tkns_arr, \
						int *i, t_list **list);
t_list	*free_list_return_null(t_list **list);

// EXECUTION OF THE TREE
//////////////////////////////////////////////
//--------------------------------------------------------
// execute_tree.c
int		ft_execute_tree(t_tree *tree);

// execute_pipe.c
int		ft_exec_pipe(t_tree *tree);
int		wait_for_all_return_chosen(int child);
int		close_pipes_return(int pipe_fd[2], int res, char const *msg);
int		ft_dopipe_in_childleft_exit(t_tree *tree, int pipe_fd[2]);
int		ft_dopipe_in_childright_exit(t_tree *tree, int pipe_fd[2]);

// execute_exec1.c
int		ft_exec_exec(t_tree *tree);
int		do_in_child_exec_exit(t_tree *tree);

// execute_exec2.c
int		ft_exec_exec_no_new_process(t_tree *tree);
char	*ft_create_address(char const *dir, char const *file);
char	*get_path_for_cmd(char *cmd, char *envp[]);
int		ft_execute_cmd_path(char *cmd, char *envp[]);
int		ft_execute_cmd(char *cmd, char *envp[]);

// execute_exec_utils.c
char	*ft_err_clear_ptr(char *res, char **paths, char const *msg1, \
						char const *msg2);
int		ft_error(int res, char const *msg1, char const *msg2);
void	ft_clear_path(char **path);
char	*get_cmd_from_list(t_list *list);
int		redef_clear_in_exec(int res, char **cmd_v, char *path, char const *msg);

// execute_semicolon_and_or_brackets.c
int		ft_exec_semicolon(t_tree *tree);
int		ft_exec_andand(t_tree *tree);
int		ft_exec_oror(t_tree *tree);
int		ft_exec_brackets(t_tree *tree);

// PART OF THE EXECUTION OF THE TREE: REDIRECTIONS
//////////////////////////////////////////////
//--------------------------------------------------------
// redirections1.c
int		do_redir_in_smaller(char const *file_out, int last_heredoc);
int		do_redir_out_bigger(char const *file_out);
int		do_redir_outout_biggerbigger(char const *file_out);
int		do_redir_inin_smallersmaller(char const *endword, t_tree *tree);
int		do_in_loop_heredoc_exit(t_tree *tree, char const *endword, \
							int pipe_fd_out);

// redirections2.c
//static int	assign_res_in_do_redir_other(t_list *ptr, int last_heredoc);
int		do_redirections_other(t_tree *tree, int last_heredoc);
int		do_redirections_heredoc(t_tree *tree);
int		do_redirections(t_tree *tree);
int		is_last_heredoc(t_tree *tree);

#endif // MINISHELL_H
