# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 18:22:10 by Ektin Op Urims    #+#    #+#              #
#    Updated: 2023/11/29 17:57:38 by Ektin Op Urims   ###   ########.fr        #
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

HEADER = minishell.h

OBJ = $(SRC:%.c=%.o)

NAME = minishell

LIBFTDIR = libft/
NAMELIBFT = $(addprefix $(LIBFTDIR), libft.a)
SHORTNAMELIBFT = -lft

CC = gcc -D DEBUG_MODE=0
CFLAGS += -Wall -Wextra -Wpedantic -Werror -g
LIBFLAGS += -lft -I$(LIBFTDIR) -L$(LIBFTDIR)
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
