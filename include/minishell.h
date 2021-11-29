/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:43 by swang             #+#    #+#             */
/*   Updated: 2021/11/25 22:08:24 by swang            ###   ########.fr       */
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
# include <signal.h>

# define SQ 32
# define DQ 64
// 128,64,32,16 8,4,2,1

# define PIPE 10

# define OUT_RE 20
# define IN_RE 21
# define HEREDOC 22
# define OUT_RE2 23

# define CMD 30

# define ARG 40

typedef	struct	s_info
{
	struct s_env_node		*env_head;
	char	**envp;
	char	**path;
	char	**token;
	unsigned char	quote;
	int		exit_stat;
	int		*real;
}	t_info;

typedef struct s_env_node
{
	char				**env_arr;
	struct s_env_node	*next;
}	t_env_node;

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
	int		index;
	int		p_fd[2]; //초기화만?
	char	**cmd; //{cmd, test, \0} -> cat > test 이런문장일때
	int		*lex; //{CMD, IN_RE,  0} -> 렉서 
	struct	s_parse_node	*prev;
	struct	s_parse_node	*next;
}	t_parse_node;

typedef struct	s_parse_list
{
	t_parse_node	*head;
	t_parse_node	*tail;
	t_parse_node	*curr;
}	t_parse_list;

/* init */ 
void	init_info(t_info *info, char *env[]);
char	**get_path(char	*envp[]);
void	make_env_list(t_info *info);

/* tokenizer_utils */
int		ft_isquote(char c);
int		ft_isredir(char c);
int		ft_ispipe(char c);
int		ft_isdoublredir(char *str);
void	check_quote_flag(char c, t_info *info);

/* tokenizser */
char	**run_tokenizer(char *line, t_info *info);
char	**divide_line(char *line, t_info *info);
void	convert_env(char **arr, t_info *info);
void	trim_quote(char **arr, t_info *info);

/* run_parsing */
t_parse_list *run_parsing(char *line, t_info *info);

/* sin_error */
int sin_lex(t_lexical_list *lex);
int sin_error(char *line);

/* lextical */
void set_lex(int c, t_lexical_list lex, t_info *info, int i);
int cmd_tok(char *tok);
t_lexical_list get_lex(t_info *info);
void init_lex(t_lexical_list lex);

#endif








