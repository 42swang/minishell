# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 15:19:54 by swang             #+#    #+#              #
#    Updated: 2021/12/24 19:51:46 by swang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L./libft -lft
LDFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include

LIB_DIR = ./libft

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
	print.c\
	signal.c\
	sin_error.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))

OBJ_DIR = obj/

OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIB_DIR) bonus
	$(CC) $(CFLAGS) $(LDFLAGS) -lreadline $(CPPFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

clean :
	make -C $(LIB_DIR) clean
	rm $(OBJS)

fclean : clean
	make -C $(LIB_DIR) fclean
	rm $(NAME)

re : fclean all

.PHONY : all clean fclean re