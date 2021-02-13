# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmalcom <qmalcom@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/02 12:56:59 by rmarguri          #+#    #+#              #
#    Updated: 2020/12/08 16:27:23 by qmalcom          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c \
		./srcs/shell_init.c \
		./srcs/minishell.c \
		./srcs/create_wlist.c \
		./srcs/create_tlist.c \
		./srcs/handle_currword_1.c \
		./srcs/handle_currword_2.c \
		./srcs/handle_quotes.c \
		./srcs/handle_dquotes.c \
		./srcs/handle_tokens.c \
		./srcs/skip_tokens.c \
		./srcs/lexer.c \
		./srcs/parser.c \
		./srcs/executor.c \
		./srcs/echo.c \
		./srcs/cd.c \
		./srcs/pwd.c \
		./srcs/env.c \
		./srcs/utils1.c \
		./srcs/utils2.c \
		./srcs/utils3.c \
		./srcs/utils4.c \
		./srcs/utils5.c \
		./srcs/export.c \
		./srcs/unset.c \
		./srcs/exit.c \
		./srcs/outer.c \
		./gnl/get_next_line.c \
		./srcs/signals.c \
		./srcs/error_func.c \
		./srcs/error_func_2.c \
		./srcs/free_structs.c

OBJS = $(SRCS:.c=.o)

CC = clang
RM = rm -f
CFLAGS = -O3 -Wall -Wextra -Werror -I.
LIBFT = ./libft/libft.a

NAME = minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

$(LIBFT):
	@$(MAKE) -C libft

$(OBJS): minishell.h

go:
	@$(MAKE) clean
	@./$(NAME)

norm:
	$(shell norminette $(SRCS) > test)
	@norminette libft/*.c >> test
	@norminette libft/*.h >> test
	@norminette minishell.h >> test
	$(if $(shell grep -e "Error" "test"),@echo "\033[0;31mNorm Error\033[0m",@echo "\033[0;32mNorme\033[0m")
	@rm test
	
clean:
	@$(MAKE) -C libft clean
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) $(LIBFT)

re: fclean $(NAME)

.PHONY:	all clean fclean re go norm