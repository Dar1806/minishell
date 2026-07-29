# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hulescur <hulescur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/05 11:19:10 by nmeunier          #+#    #+#              #
#    Updated: 2026/07/20 17:03:43 by hulescur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstdelone.c \
		libft/ft_strlen.c libft/ft_itoa.c libft/ft_bzero.c libft/ft_atoi.c\
		libft/ft_putnbr_fd.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c \
		libft/ft_putstr_fd.c libft/ft_strrchr.c libft/ft_toupper.c \
		libft/ft_strmapi.c libft/ft_striteri.c libft/ft_strnstr.c \
		libft/ft_lstclear.c libft/ft_lstiter.c libft/ft_lstmap.c \
		libft/ft_strlcat.c libft/ft_strncmp.c libft/ft_strlcpy.c \
		libft/ft_isalnum.c libft/ft_isprint.c libft/ft_isdigit.c \
		libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_tolower.c \
		libft/ft_lstnew.c libft/ft_lstsize.c libft/ft_lstlast.c \
		libft/ft_isalpha.c libft/ft_isascii.c libft/ft_memchr.c \
		libft/ft_memmove.c libft/ft_memset.c libft/ft_substr.c \
		libft/ft_calloc.c libft/ft_memcmp.c libft/ft_memcpy.c \
		libft/ft_strdup.c libft/ft_strchr.c libft/ft_split.c \
		libft/ft_garbage.c libft/ft_ft_split.c \

SRCS = $(LIBFT) src/main.c src/lexer/lexer.c src/lexer/fill_lexer.c \
				src/free/free.c src/parser/parser.c src/parser/env.c \
				src/parser/fill_parser.c src/exec/setup_exec.c\
				src/exec/exec_cmd.c src/exec/here_doc.c \
				src/exec/set_std.c src/exec/get_path.c \
				src/exec/pipe_exec.c src/parser/is_type.c

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
RDFLAGS = -lreadline

NAME = minishell
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(RDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus_re: fclean bonus

.PHONY: all bonus clean fclean re bonus_re

