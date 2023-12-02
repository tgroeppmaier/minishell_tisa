# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminakov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 15:04:27 by aminakov          #+#    #+#              #
#    Updated: 2023/11/20 11:38:17 by aminakov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_atoi_0x.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_split_aux.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putnbr_base_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_printf.c \
	ft_printf_fd.c \
	ft_printf_bonus.c \
	ft_printf_bonus_aux.c \
	ft_printf_bonus_second_aux.c \
	get_next_line.c \
	get_next_line_utils.c \

HEADER = libft.h
OBJ = $(SRC:.c=.o)

NAME = libft.a
SHORTNAME = -lft

CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Werror
NORM = /bin/norminette

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

%.o:	%.c NORM
	$(CC) -o $@ -c $< $(CFLAGS)

NORM:
	@if [ "$(wildcard $(NORM))" != "" ]; then\
		 $(NORM) $(SRC) $(HEADER);\
	fi

clean:
	rm -f $(wildcard *.o) $(wildcard *.h.gch) $(wildcard .*.swp)

fclean:	clean
	rm -f $(wildcard *.a) $(wildcard .out) $(wildcard *.so)

re:
	make fclean
	make all

.PHONY: clean fclean re
