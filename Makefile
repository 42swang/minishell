# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 15:19:54 by swang             #+#    #+#              #
#    Updated: 2022/01/24 18:05:04 by swang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

LDFLAGS = -L${HOME}/.brew/opt/readline/lib
CPPFLAGS= -I${HOME}/.brew/opt/readline/include

MAKE = make

SRC_DIR = src/

SRC_NAME = ft_cd.c\
	ft_cd_utils.c\
	ft_exit.c\
	lexer_check_utils2.c\
	lexer_check_utils.c\
	redirection.c\
	redirection_utils.c\
	signal.c\
	sin_error.c\
	builtin.c\
	execute.c\
	find_cmd_path.c\
	free_line.c\
	free_list.c\
	ft_echo.c\
	ft_env.c\
	ft_export_utils.c\
	ft_export.c\
	ft_export2.c\
	ft_heredoc.c\
	ft_pwd.c\
	ft_unset.c\
	init_term.c\
	init.c\
	main.c\
	make_cmd_arr.c\
	make_env_list.c\
	make_lex_node.c\
	make_path_arr.c\
	parsing.c\
	pipe_redir.c\
	run_lexer.c\
	run_parser.c\
	run_pipe.c\
	run_tokenizer.c\
	tokenizer_convert_env.c\
	tokenizer_divide.c\
	tokenizer_trim_quote.c\
	tokenizer_utils.c\
	tokenizer_utils2.c

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
