/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:43 by swang             #+#    #+#             */
/*   Updated: 2022/01/20 20:12:54 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>

# define SQ 32
# define DQ 64
# define PIPE 100
# define IN_RE 200
# define IN_FILE 201
# define HEREDOC 300
# define HERE_DEL 301
# define OUT_RE 400
# define OUT_FI 401
# define OUT_RE2 500
# define OUT_FI2 501
# define CMD 555
# define OPT 556
# define ARG 557

typedef struct	s_glovar
{
	int	g_exit_status;
	struct termios	old_term;
	struct termios	new_term;
}	t_glovar;

t_glovar	glovar;

typedef	struct	s_info
{
	int						*real;
	int						file_idx;
	int						*file;
	int						exit_stat;
	char					**envp;
	char					**path;
	char					**token;
	char					**cmd_arr;
	char					*old_pwd;
	char					*home;
	unsigned char			quote;
	struct s_env_list		*env_list;
	struct s_lex_list		*lex_list;
	struct s_parse_list		*parse_list;
}	t_info;

typedef struct	s_env_node
{
	char				**env_arr;
	struct s_env_node	*prev;
	struct s_env_node	*next;
}	t_env_node;

typedef struct	s_env_list
{
	struct s_env_node	*head;
	struct s_env_node	*tail;
	struct s_env_node	*curr;
}	t_env_list;

typedef struct	s_lex_node
{
	int					type;
	char				*value;
	struct s_lex_node	*prev;
	struct s_lex_node	*next;
}	t_lex_node;

typedef struct	s_lex_list
{
	t_lex_node	*head;
	t_lex_node	*tail;
	t_lex_node	*curr;
}	t_lex_list;

typedef struct	s_parse_node
{
	int		index;
	int		p_fd[2];
	char	**cmd;
	int		*lex;
	struct	s_parse_node	*prev;
	struct	s_parse_node	*next;
}	t_parse_node;

typedef struct	s_parse_list
{
	t_parse_node	*head;
	t_parse_node	*tail;
	t_parse_node	*curr;
}	t_parse_list;


/* free */
void	free_info(t_info *info);
void	free_list(t_info *info);
void	ft_free(char **str);
void	free_2d(char **arr);
void	free_line(t_info *info, char *line);

/* init */
void	init_info(t_info *info, char **envp);
void	sig_init(void);
void	use_arg(int ac, char **av);




int	count_arr(char **arr);

int		check_sign(char *str, t_info *info);
char	**get_path(t_env_list *list);
t_env_list	*make_env_list(char **envp);

/* tokenizser */
char	**run_tokenizer(char *line, t_info *info);
char	**divide_line(char *line, t_info *info);
char	**convert_env(char **arr, t_info *info);
char	**trim_quote(char **arr, t_info *info);

/* tokenizer_utils */
int		ft_isquote(char c);
int		ft_isredir(char c);
int		ft_ispipe(char c);
int		ft_isdoublredir(char *str);
void	check_quote_flag(char c, t_info *info);

/* lexer */
t_lex_list *run_lexer(t_info *info);
t_lex_node	*make_lex_node(int type, char *tok);

/* lexer_utils */
int ft_check_cmd(t_info *info, int i, t_lex_list *lex_list);
int ft_check_opt(char *tok, t_info *info, int i, t_lex_list *lex_list);
int ft_check_file(t_info *info, int i);
t_lex_node	*ft_check_inout(char *tok, t_lex_list *lex_list);

/* parser */
t_parse_list	*run_parser(t_info *info);

/* sin_error */
int sin_lex(t_lex_list *lex);
int sin_error(char *line);

/* src */
void	delete_line(t_info *info, char *line);
int	parsing(char *line, t_info *info);
void ft_execute(t_info *info);


/* re */
void	pre_open(t_info *info);
void	redirection(t_info *info, t_parse_node *p);


/* execute utils*/
int		ft_isbuiltin(char *tok);
char **make_cmd_arr(t_parse_node *p, t_info *info);
char *find_cmd_path(char **arr, char *cmd);


/* built-in */
int	ft_env(t_info *info);
int	ft_export(t_info *info, t_parse_node *p, int i);
int	ft_unset(t_info *info, t_parse_node *p, int i);

/* for test*/
void	ft_print_env_list(t_env_list *ptr);
void	ft_print_parse_list(t_info *info);
void	ft_print_str_arr(char **arr);
void	ft_print_lex_list(t_info *info);

void handle_signal(int signo);
void	here_document(t_parse_node *p, int idx);
void	ft_isheredoc(t_info *info);
void	find_heredoc_p(t_parse_node *p);
int ft_exit(t_parse_node *p, t_info *info);
int	ft_atoi_for_exit(char *str);
t_env_node	*make_env_node(char *str);
void run_builtin(t_parse_node *p, t_info *info);
int ft_echo(t_parse_node *p, t_info *info);
int ft_pwd(t_parse_node *p, t_info *info);
int				ft_cd(t_parse_node *p, t_info *info);
char	*get_env_path(t_env_node *env, const char *var);
void	free_info(t_info *info);
int	check_no_pipe_builtin(t_info *info);

#endif
