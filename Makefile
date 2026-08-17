# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/05 11:19:10 by nmeunier          #+#    #+#              #
#    Updated: 2026/08/18 01:15:24 by akkolitozer      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstdelone.c \
		libft/ft_strdup.c libft/ft_strchr.c libft/ft_split.c libft/ft_strcmp.c\
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
		libft/ft_garbage.c libft/ft_ft_split.c libft/ft_strnjoin.c\

SRCS = $(LIBFT) src/main.c src/lexer/lexer.c src/lexer/fill_lexer.c \
				src/free/free.c src/parser/parser.c src/expander/env_list.c \
				src/expander/expander.c  src/expander/env_array.c\
				src/parser/fill_parser.c src/exec/setup_exec.c\
				src/builtins/builtins.c src/builtins/echo.c \
				src/builtins/export.c src/builtins/export2.c \
				src/exec/pipe_exec.c src/parser/is_type.c \
				src/exec/exec_cmd.c src/exec/here_doc.c \
				src/exec/set_std.c src/exec/get_path.c \
				src/builtins/cd.c src/builtins/pwd.c \
				src/builtins/unset.c src/builtins/env.c \
				src/builtins/export3.c src/builtins/exit.c

CC = cc
RM = rm -f
INC_DIR = includes
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)
RDFLAGS = -lreadline

NAME = minishell
OBJS = $(SRCS:.c=.o)
TOTAL := $(words $(SRCS))
N := 0

# Colors
GREEN   = \033[0;32m
CYAN    = \033[0;36m
YELLOW  = \033[0;33m
RED     = \033[0;31m
MAGENTA = \033[0;35m
RESET   = \033[0m
BOLD    = \033[1m

all: $(NAME)

$(NAME): banner_start $(OBJS)
	@printf "$(YELLOW)Linking minishell...$(RESET)\n"
	@$(CC) $(OBJS) $(RDFLAGS) -o $(NAME)
	@printf "\n"
	@printf "$(BOLD)\033[1;37m"
	@printf '%s\n' '		                                                 '
	@printf '%s\n' '		                     .++##=                      '
	@printf '%s\n' '		                  .*****###**-                   '
	@printf '%s\n' '		              ..**+*****%###****=                '
	@printf '%s\n' '		           ..=*+++******#%###****+=-             '
	@printf '%s\n' '		         .=+=+=++*******#%%###*#*+*+=*           '
	@printf '%s\n' '		        :++====++*******##%###****+*=**:         '
	@printf '%s\n' '		       *+===++*******#**##%%##**#*+*++*==        '
	@printf '%s\n' '		      *+..++**#***+*****%#####*****+=+=-:+       '
	@printf '%s\n' '		     *+=...=:===*=++**##%#####**=++++==--::      '
	@printf '%s\n' '		    ++++=*+====..+.++**#%#%#*+++++===--**:+*     '
	@printf '%s\n' '		    +*++===***+==...=.*-*%+.:+===++**++**+++:    '
	@printf '%s\n' '		   =****#**###***++++++.@#:*####%%%@@#@%##+=:    '
	@printf '%s\n' '		    #*%%%%%%%#=.....%%#**+%%%%%%%%%%%%%%%#*+     '
	@printf '%s\n' '		   .=#+--------+*###%%%%%@%#**#*+--------+#=.=   '
	@printf '%s\n' '		  @@%#                  #+.               **@@%  '
	@printf '%s\n' '		    **                 ./+*               .#     '
	@printf '%s\n' '		    **+              =/..==++            :+*     '
	@printf '%s\n' '		    ***+++--____==+++=...++=++++____===--:::     '
	@printf '%s\n' '		    *%#=%%%::+=#*#+=+....+++=+=++++++===--#@     '
	@printf '%s\n' '		    ###%%%#-%%%##++**...-=+*=##*+=+++=%##+*%     '
	@printf '%s\n' '		      ##%%%%#####.=#:....++%###*=+*%%%%##*+      '
	@printf '%s\n' '		        %%%%%.####*#.:..+@@%###-=+*#%%%#:        '
	@printf '%s\n' '		          %%#*####*#+#.%@%##*##=#*####           '
	@printf '%s\n' '		           #%####>*#%%#%#%%####*<%%%#            '
	@printf '%s\n' '		           ######-              -%%%#            '
	@printf '%s\n' '		            #%###*              .%%%*            '
	@printf '%s\n' '		            %%.%#.              .=%%             '
	@printf '%s\n' '		            %%.#%-              .#%%             '
	@printf '%s\n' '		            %%###%              %%%%             '
	@printf '%s\n' '		             %%##%              %%%*             '
	@printf '%s\n' '		             %%###             .%%#              '
	@printf '%s\n' '		             #%*#*             *%%%              '
	@printf '%s\n' '		             %%.##             %%%%              '
	@printf '%s\n' '		             :%=##             *%%*              '
	@printf '%s\n' '		              %##/             *%%.              '
	@printf "$(RESET)\n"
	
	@printf '%s\n' '___  ________ _   _ _____ _____ _   _  _____ _      _      ______ _____  ___ ________   __'
	@printf '%s\n' '|  \/  |_   _| \ | |_   _/  ___| | | ||  ___| |    | |     | ___ \  ___|/ _ \|  _  \ \ / /'
	@printf '%s\n' '| .  . | | | |  \| | | | \ `--.| |_| || |__ | |    | |     | |_/ / |__ / /_\ \ | | |\ V / '
	@printf '%s\n' '| |\/| | | | | . ` | | |  `--. \  _  ||  __|| |    | |     |    /|  __||  _  | | | | \ /  '
	@printf '%s\n' '| |  | |_| |_| |\  |_| |_/\__/ / | | || |___| |____| |____ | |\ \| |___| | | | |/ /  | |  '
	@printf '%s\n' '\_|  |_/\___/\_| \_/\___/\____/\_| |_/\____/\_____/\_____/ \_| \_\____/\_| |_/___/   \_/'
	@printf "$(RESET)\n"

banner_start:
	@printf "$(MAGENTA)$(BOLD)ATM git:(main) make$(RESET)\n"
	@printf "$(MAGENTA)Construction de la Libft...$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(CYAN)Compiling:$(RESET)%s\n" "$<"

libft_done:
	@printf "$(GREEN)libft.a est compilé avec succès$(RESET)\n"

clean:
	@$(RM) $(OBJS)
	@printf "$(RED)Objets supprimés$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)$(NAME) supprimé$(RESET)\n"

re: fclean all

bonus_re: fclean bonus

.PHONY: all bonus clean fclean re bonus_re banner_start libft_done
