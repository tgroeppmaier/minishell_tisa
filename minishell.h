/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:49:23 by aminakov          #+#    #+#             */
/*   Updated: 2023/12/13 14:52:08 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -D DEBUG_MODE=1 : 1-debug; 0-performance. 4 */
# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

// 0: get_next_line, 1: readline
# ifndef READLINE_MODE
#  define READLINE_MODE 0
# endif

# if (READLINE_MODE == 1)
#  ifdef SHELL_NAME
#   undef SHELL_NAME
#  endif
#  define SHELL_NAME "Tisa"
# endif

# if (READLINE_MODE == 0)
#  ifdef SHELL_NAME
#   undef SHELL_NAME
#  endif
#  define SHELL_NAME "tisa"
# endif

// 1 for restoring PWD, OLDPWD (like in zsh), 0 for not (like in bash)
# ifndef RESTORE_PWD_MODE
#  define RESTORE_PWD_MODE 0
# endif

// 1 for setting GPID (like in bash), 0 for playing with resetting signals
# ifndef GPID_MODE
#  define GPID_MODE 1
# endif

# include "libft.h"
# include <sys/wait.h> // waitpid(-1, NULL, 0);
# include <errno.h> // for while (wait(NULL!=-1||errno!=ECHILD))
# include <fcntl.h> // open, O_RDONLY, O_WRONLY
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h> // readline
# include <stdbool.h> // bool true false
# include <signal.h> // signals. But already in sys/wait.h

/* do not use the combination GREEN RES, instead use GREEN WHITE, 
because in the first case pressing TAB and then backslash allows 
to enter last printed character
just GREEN with TAB + BACKSLASH allows to enter several printed charachters
*/

//# define RES "\001\033[0m\002"
# define RES "\033[0m"
# define BLINKING "\033[5m"
# define RED "\033[31m"
# define BUFF_RED "\001\033[41m\002"
# define GREEN "\033[32m"
# define BUFF_GREEN "\033[42m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define LBL "\033[36m"
# define GREY "\033[37m"
# define WHITE "\033[39m"

# ifndef GREEN_MODE
#  define GREEN_MODE 1
# endif

# if GREEN_MODE == 1
#  define OPTGREEN GREEN
#  define OPTWHITE WHITE
# elif GREEN_MODE == 0
#  define OPTGREEN ""
#  define OPTWHITE ""
# endif

# define NO_SIGNAL 0
# define SIGINT_RECEIVED 1
# define SIGQUIT_RECEIVED 2

/* BUGS:
	- for tabs or spaces returns an error. FIXED
	- does not free space for Ctrl+C, Ctrl+\.
	  Surprisingly, it works for Ctrl+D. But maybe not as expected?
	  Yes, not as expected.
	- copying and pasting into tisa minishell makes it directly executed.
	  copying without newline works. But the normal shell does not do it
	  anyway.
	- Timo 1Dec2023: echo "Hi">file.txt will write "Hi", but should write Hi.
	  So, each not quoted quote should be removed.
	  This should be done after tokenization is done,
	  together with expansion of $VARIABLES.
	- With green welcome message, if you type more than 80 charachters, and then
	  backslash, you will eat some of the characters which you are not allowed.
	- running minishell in minishell, and then kill old_shell
	  causees shell to be infinitely printed.
	  Doing the same in minishell->bash,
	  leads to the problem with Enter upon next execution of minishell.
	  Enter will be interpreted as ^M.

	- env . should give Permission denied, but gives No such file or directory
	  mkdir new_dir; env new_dir/ or env_new_dir// -- same
*/

extern volatile sig_atomic_t	g_sigint_received;

/* I first though to include a field t_tree *tree in s_data,
but there is just one data, and many subtrees (every node is a subtree).
So it is not clear which tree should correspond to the data.
Hence, I deleted the pointer to tree. Hence, we should always prototype
functions to take tree as an argument, not data.*/
typedef struct s_data
{
	char	**envp;
	char	*working_dir;
	char	*old_working_dir;
	char	builtins[100];
	int		exit_code;
}	t_data;

typedef struct s_interval
{
	int	b;
	int	e;
}	t_sgm;

typedef enum e_node {SEMICOLON, PIPE, ANDAND, OROR, BRACKETS, \
			IN, ININ, OUT, OUTOUT, EXEC}	t_node;

/* heredoc_pipes will exist only for the head of the tree */
/* sigpid will only make sense for the head of the tree */
/* data exists for all trees, even though it is the same data */
typedef struct s_tree
{
	char			*cmd;
	struct s_tree	*left_child;
	struct s_tree	*right_child;
	struct s_tree	*head;
	t_list			*list;
	struct s_data	*data;
	int				(*heredoc_pipes)[2];
	int				heredoc_cnt;
	int				beg;
	int				end;
	int				level;
	int				bene;
	int				do_in_child_process;
	int				is_builtin;
	int				gpid;
	t_node			node;
}	t_tree;

typedef struct s_CreateNewStrArgs
{
	const char	*str;
	char		*new_str;
	int			*j;
	char		*exit_code_str;
}	t_CreateNewStrArgs;

// print_error.c
int		print_error(int res, char const *str);
int		perr2(int res, char const *str, char ch);
int		perr3(int res, char const *str, char ch, int num);
int		print_error_grammar(int res, t_node node);
int		print_error_syntax(int res, t_list *list);

// print_error2.c
int		print_err_empty_str_in_cmd(int res, char const *cmd);

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
int		is_str_one_of_setstr(char const *str, char const *setstr);
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
int		show_prompt(t_data *data);
int		do_free_str(char **str);

// show_prompt_readline.c
void	set_base_msg_tree_bene(char *base_msg, int size, \
				t_tree **tree, int *bene);
int		set_welcome_msg(char *welcome_msg, int size, int num);
void	process_line(t_data *data, char *str, t_tree *tree, int *bene);
//static void	check_for_sigint_received(t_data *data);
int		show_prompt_readline(t_data *data);

// show_prompt_readline_utils.c
int		clear_history_return_exit_code(int exit_code);

// CREATION OF THE TREE
//////////////////////////////////////////////
//--------------------------------------------------------
// create_tree.c
int		create_tree(t_tree **tree, char *str, t_sgm sgm, t_data *data);
int		do_if_sep(t_tree *tree, int sep_pos, t_node sep);
int		doifbrackets_in_create_tree(t_tree *tree, t_sgm brackets);
int		set_separate_pos(char const *str, t_sgm sgm, t_node *sep);
int		check_input_str_sgm(char const *str, t_sgm sgm);

// create_tree_aux.c
void	prefill_node(t_tree *tree, char *str, t_sgm sgm, t_data *data);
void	free_tree(t_tree **tree);
void	print_tree(t_tree *tree);
void	create_display_free_tree(t_tree **tree, char *str, int mode, \
							t_data *data);

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

// create_tree_post_processing2.c
int		does_list_have_mistakes(t_list *list);
int		do_exec_nodes_have_mistakes(t_tree *tree);

// processing_of_exec_nodes.c
int		expand_exec_nodes(t_tree *tree);
int		expand_exec_nodes_count_heredocs(t_tree *tree);
//int		expand_exec_nodes_together_with_quotes_removal(t_tree *tree);

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
/* static int	init_list_i(t_list **list, int *i, char ***tkns_arr, \
						char const *tkns);*/
/* static void	set_b_decrease_i(t_sgm *sgm, int *i); */
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
int		treat_heredocs_execute_tree(t_tree *tree);
int		do_fork_set_gpid(t_tree *tree);
int		do_clean_and_exit(int res, t_tree *tree);

// execute_pipe.c
int		ft_exec_pipe(t_tree *tree);
int		wait_for_all_return_chosen(int child);
int		close_pipes_return(int pipe_fd[2], int res, char const *msg);
int		ft_dopipe_in_childleft_exit(t_tree *tree, int pipe_fd[2]);
int		ft_dopipe_in_childright_exit(t_tree *tree, int pipe_fd[2]);

// execute_exec1.c
int		set_signals(void);
int		unset_signals(void);
//int		create_child_and_setup_signals(t_tree *tree);
//int		wait_for_child_and_restore_signals(t_tree *tree, int child);
int		ft_exec_exec(t_tree *tree);
int		do_in_child_exec_exit(t_tree *tree);
int		restore_signals_in_children(void);

// execute_exec2.c
int		ft_exec_exec_no_new_process(t_tree *tree);
char	*ft_create_address(char const *dir, char const *file);
char	*get_path_for_cmd(char *cmd, char *envp[]);
int		ft_execute_cmd_path(char **vector_cmd, char *envp[]);
int		ft_execute_cmd(char **vector_cmd, char *envp[]);

// execute_exec_utils.c
char	*ft_err_clear_ptr(char *res, char **paths, char const *msg1, \
						char const *msg2);
int		ft_error(int res, char const *msg1, char const *msg2);
void	ft_clear_path(char **path);
//char	*get_cmd_from_list(t_list *list);
char	**get_vector_from_list(t_list *list);
int		redef_clear_in_exec(int res, char **cmd_v, char *path, char const *msg);

// execute_semicolon_and_or_brackets.c
int		ft_exec_semicolon(t_tree *tree);
int		ft_exec_andand(t_tree *tree);
int		ft_exec_oror(t_tree *tree);
int		ft_exec_brackets(t_tree *tree);

// copy_file_descriptors.c
int		make_a_copy_of_fd(t_sgm *sgm, t_tree *tree);
int		restore_file_descriptors_close_copies(t_sgm sgm, t_tree *tree);

// PART OF THE EXECUTION OF THE TREE: REDIRECTIONS
//////////////////////////////////////////////
//--------------------------------------------------------
// redirections1_initial_heredoc_treatment.c
int		count_heredocs_in_tree(t_tree *tree, int *cnt);
int		create_and_open_pipes_for_heredocs(t_tree *tree);
int		print_pipes_that_were_created(t_tree *tree);
int		close_all_heredoc_pipes_except(t_tree *tree, int r, int w);

// redirections2_initial_heredoc_treatment.c
int		redirect_all_heredocs_to_pipes(t_tree *tree);
int		redirect_heredocs_to_pipes_recursively(t_tree *tree);
int		redirect_heredocs_to_pipes(t_tree *tree);
int		do_redir_inin_part1_write_to_pipe(char const *endword, \
						int pipe_num, t_tree *tree);
int		do_in_loop_heredoc(char const *endword, int pipe_fd_out);

// redirections3.c
int		do_redir_in_smaller(char const *file_out);
int		do_redir_out_bigger(char const *file_out);
int		do_redir_outout_biggerbigger(char const *file_out);
int		do_redir_inin_part2_read_from_pipe(int pipe_num, t_tree *tree);

// redirections4.c
//static int	assign_res_in_do_redir(t_list *ptr, int last_heredoc);
int		do_redirections(t_tree *tree);

// SIGNAL handling
//////////////////////////////////////////////
//--------------------------------------------------------
// signals.c
void	handle_sigtstp(int n);
void	handle_sigcont(int n);
void	handle_sigint(int n);
void	signals_treating(t_data *data);
void	handle_sigint_eof(int sig);

// BUILTINS
//////////////////////////////////////////////
//--------------------------------------------------------
// builtin_env.c
int		set_data(t_data *data, char **envp);
int		print_env(char **envp);
int		count_env(char **envp);
char	**copy_environ(char **envp, int additional_space);
int		builtin_env(t_tree *tree);

// builtin_unset.c
void	free_envp(char ***envp);
void	free_data_except_tree(t_data *data);
void	remove_var(t_data *data, char *var_name);
int		builtin_unset(t_tree *tree);

// builtin_main.c
int		check_if_builtin_set_no_child_process(t_tree *tree);
int		exec_int_function(t_tree *tree);

// builtin_exit.c
bool	is_in_range(long long num);
bool	is_valid_int(char *str);
int		builtin_exit(t_tree *tree);

// builtin_export.c
int		add_var(char *var_name, t_data *data);
int		var_index(char *var_name, char **envp);
/*bool	is_valid_name(char *var_name);*/
int		update_var(char *var_name, t_data *data);
int		builtin_export(t_tree *tree);

// builtin_echo.c
/*static bool		check_n(char *word);*/
int		builtin_echo(t_tree *tree);

// builtin_pwd.c
char	*ft_getenv(char *var_name, t_data *data);
int		builtin_pwd(t_tree *tree);

// builtin_cd.c
void	set_env_value(t_data *data, char *var_name, char *value);
//void	update_path(t_data *data);
/*static int	do_if_failed_cd(char const *path);*/
/*static void	do_update_var_free_str(char **ptr, t_data *data);*/
int		change_directory(t_data *data, char const *path);
int		builtin_cd(t_tree *tree);

// QUOTES REMOVAL VARIABLES EXPANSION
//////////////////////////////////////////////
//--------------------------------------------------------
// expand_quotes.c
size_t	calculate_buffer_size(char const *str);
void	copy_without_quotes(char *dest, char const *src);
void	remove_outer_quotes(char **str);
void	expand_quotes(t_tree *tree);
void	expand_quotes_all_tree(t_tree *tree);

// expand_variables.c
bool	in_single_quotes(char const *str, int index);
int		skip_copy(int *i, int *k, char *str, char *expand);
void	expand_str(t_tree *tree, char *str, char *expand, int len);
void	expand_variables(t_tree *tree);
void	expand_variables_all_tree(t_tree *tree);

// expand_variables_helper.c
int		get_varname_len(char *str);
char	*get_var_name(char *str);
int		skip_count(int *i, int *len, char *str);
int		get_expand_len(t_tree *tree, char *str, int i, int len);

// expand_exit_code.c
/* static int		calculate_new_len(const char *str, \
				int i, char *exit_code_str); */
// static void	create_new_str(t_CreateNewStrArgs args, int i);
/* static char	*expand_exit_code_rest(const char *str, \
				char *exit_code_str, int i); */
char	*expand_exit_code(const char *str, char *exit_code_str, int i);
void	expand_exit(t_tree *tree, int exit_code);

#endif // MINISHELL_H
