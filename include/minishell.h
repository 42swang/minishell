/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:43 by swang             #+#    #+#             */
/*   Updated: 2021/11/21 01:09:34 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/* readline 함수, add_history함수, exit, printf, 동적할당 */

typedef	struct	s_info
{
	char	**path;
	char	**token;
}	t_info;

typedef struct	s_lexical_node
{
	int		type;
	char	*value;
	struct s_lexical_node	*prev;
	struct s_lexical_node	*next;
}	t_lexical_node;

typedef struct	s_lexical_list
{
	t_lexical_node	*head;
	t_lexical_node	*tail;
	t_lexical_node	*curr;
}	t_lexical_list;

typedef struct	s_parse_node
{
	int		order;
	int		p_fd[2];
	char	*cmd;
	struct	s_parse_node	*prev;
	struct	s_parse_node	*next;
}	t_parse_node;

typedef struct	s_parse_list
{
	t_parse_node	*head;
	t_parse_node	*tail;
	t_parse_node	*curr;
}	t_parse_list;

//parse 노드 미완성

/* utils */
void	init_info(t_info *info);
char	**get_path(char	*envp[]);


/* split */
char	**ft_split_cmd(char const *s, char c);
int		check_quotation_mark(char *str, int *i);
int		find_start_end(char *s, int *i, int *start, char c);

/* parsing */
t_parse_list *run_parsing(char *line, t_info *info);

/* src */


/* tokenizser */
char	**get_token(char *line);

/* lexer */

/* parser */


#endif