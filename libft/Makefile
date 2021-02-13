# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/29 16:09:53 by rmarguri          #+#    #+#              #
#    Updated: 2020/10/30 15:29:22 by rmarguri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
COMP = clang
FLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
ft_tolower.c ft_toupper.c ft_nbrlen.c ft_strnchr.c \
ft_lst_push_back.c ft_lst_push_front.c ft_lstadd.c \
ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
ft_lstnew.c ft_lstlast.c ft_lstlen.c ft_atol.c \
ft_strnew.c ft_strclr.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@ar -rcs $(NAME) $(OBJ)

%.o: %.c
	@$(COMP) $(FLAGS) -c $< -o $@

go:
	clang main.c $(NAME)
	./a.out

clean:
	@rm -rf *.o ./src/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, go, re, clean, fclean
