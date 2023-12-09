# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 18:22:10 by aminakov          #+#    #+#              #
#    Updated: 2023/12/09 13:24:49 by tgroeppm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	minishell.c \
	print_error.c \
	parsing.c \
	segment.c \
	parsing_aux_find_symb.c   last_parsing_aux_find_symb.c \
	parsing_aux_find_str.c    last_parsing_aux_find_str.c \
	parsing_quotes_1.c        last_parsing_quotes_1.c \
	parsing_quotes_2.c \
	parsing_brackets_1.c      last_parsing_brackets_1.c \
	parsing_brackets_2.c      last_parsing_brackets_2.c \
	show_prompt.c \
	show_prompt_readline.c \
	create_tree.c \
	create_tree_aux.c \
	create_tree_find_sep_or_brackets.c \
	create_tree_post_processing1.c \
	create_tree_post_processing2.c \
	separators.c \
	ft_split_quotes_tkns.c \
	wc_quotes_tkns.c \
	processing_of_exec_nodes.c \
	execute_tree.c \
	execute_pipe.c \
	execute_exec1.c \
	execute_exec2.c \
	execute_exec_utils.c \
	execute_semicolon_and_or_brackets.c \
	redirections1.c \
	redirections2.c \

SRC +=	builtin_env.c \
	builtin_unset.c \
	builtin_main.c \
	builtin_exit.c \
	builtin_export.c \
	builtin_echo.c \
	builtin_pwd.c \
	builtin_cd.c \

SRC += expand_variables.c \
	expand_variables_helper.c \
	expand_quotes.c \
	
SRC += signals.c \
	
HEADER = minishell.h

OBJ = $(SRC:%.c=%.o)

NAME = minishell

LIBFTDIR = libft/
NAMELIBFT = $(addprefix $(LIBFTDIR), libft.a)
SHORTNAMELIBFT = -lft

# for performance: DEBUG_MODE 0, READLINE_MODE 1, GREEN_MODE=0. 
# if RESET_PWD_MODE is 1, it will restore PWD, OLD_PWD even if they 
#	were unsetted (like in zsh).
# if RESET_PWD_MODE is 0, it will not restore them (like in bash).

# With GREEN_MODE 1, after entering more than 80 spaces (or a dozen of tabs),
# and backslashing, you can erase some before written symbols.
# No, the problem persisted even without green.
#  But only in get_next_line mode, not in readline_mode.
#  So, in readline_mode with green the problem persists, without green_mode not.
# The problem persisted even after increasing BUFFER_SIZE in libft

CC = cc
CC += -D DEBUG_MODE=0
CC += -D READLINE_MODE=1
CC += -D RESET_PWD_MODE=0
CC += -D GREEN_MODE=1
CFLAGS += -Wall -Wextra -Wpedantic -Werror -g
LIBFLAGS += -lft -I$(LIBFTDIR) -L$(LIBFTDIR)
LIBFLAGS += -lreadline
NORM = /bin/norminette

all: $(NAME)

$(NAME): $(NAMELIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS)
	make NORM

%.o:	%.c $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS) -Ilibft

$(NAMELIBFT):
	make -C $(LIBFTDIR)

NORM:
	@if [ "$(wildcard $(NORM))" != "" ]; then \
		$(NORM) $(SRC) $(HEADER); \
	fi

clean:
	make -C $(LIBFTDIR) clean
	rm -f $(wildcard *.o) $(wildcard *.h.gch)
	rm -f $(wildcard .*.swp) $(wildcard .*.swo) $(wildcard .*.swx)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(wildcard *.a) $(wildcard *.out) $(wildcard *.so) $(NAME)

re:
	make fclean
	make

#SHELL := /bin/bash
#	@echo $(SHELL)
#	@if [ "" != "$(findstring READLINE_MODE=1, $(CC))" ]; then \
#		echo READLINE_MODE; \
#		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS) -lreadline; \
#		echo READLINE_MODE; \
#	else \
#		echo GET_NEXT_LINE_MODE; \
#		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS) -lreadline; \
#		echo GET_NEXT_LINE_MODE; \
#	fi
