CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell_test
LIBS = -lreadline
SRC = main_builtin_test.c builtin_export.c libft.c builtin_env.c builtin_exit.c builtin_echo.c builtin_pwd.c builtin_cd.c builtin_unset.c
OBJ = $(SRC:.c=.o)
HEADER = minishell.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
