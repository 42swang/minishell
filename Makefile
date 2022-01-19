# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 15:19:54 by swang             #+#    #+#              #
#    Updated: 2022/01/19 19:33:11 by swang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a

LDFLAGS = -L${HOME}/.brew/opt/readline/lib
CPPFLAGS= -I${HOME}/.brew/opt/readline/include

MAKE = make

SRC_DIR = src/

SRC_NAME = main.c\
	init.c\
	make_env_list.c\
	tokenizer_divide.c\
	tokenizer_convert_env.c\
	tokenizer_utils.c\
	parsing.c\
	run_tokenizer.c\
	tokenizer_trim_quote.c\
	run_lexer.c\
	lexer_check_utils.c\
	run_parser.c\
	make_path_arr.c\
	make_cmd_arr.c\
	delete_data.c\
	execute.c\
	find_cmd_path.c\
	ft_env.c\
	ft_unset.c\
	redirection.c\
	print.c\
	signal.c\
	ft_heredoc.c\
	ft_exit.c\
	ft_echo.c\
	ft_export.c\
	ft_pwd.c\
	ft_cd.c\
	sin_error.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) ${SRCS} ${LIBFT} -lreadline ${LDFLAGS} ${CPPFLAGS} -o ${NAME}

${LIBFT}:
			make -C ./libft
clean :
		make -C ./libft clean
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(OBJS) ${NAME}
		make -C ./libft fclean
re : fclean $(NAME)

.PHONY : all clean fclean re
