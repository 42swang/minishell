/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:43 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:32:06 by swang            ###   ########.fr       */
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

typedef struct s_glovar
{
	int				g_exit_status;
	struct termios	origin_term;
	struct termios	gaepo_term;
}	t_glovar;

t_glovar			g_glovar;

typedef struct s_info
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

typedef struct s_env_node
{
	char				**env_arr;
	struct s_env_node	*prev;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	struct s_env_node	*head;
	struct s_env_node	*tail;
	struct s_env_node	*curr;
}	t_env_list;

typedef struct s_lex_node
{
	int					type;
	char				*value;
	struct s_lex_node	*prev;
	struct s_lex_node	*next;
}	t_lex_node;

typedef struct s_lex_list
{
	t_lex_node	*head;
	t_lex_node	*tail;
	t_lex_node	*curr;
}	t_lex_list;

typedef struct s_parse_node
{
	int					index;
	int					p_fd[2];
	char				**cmd;
	int					*lex;
	struct s_parse_node	*prev;
	struct s_parse_node	*next;
}	t_parse_node;

typedef struct s_parse_list
{
	t_parse_node	*head;
	t_parse_node	*tail;
	t_parse_node	*curr;
}	t_parse_list;

/* main */
int				parsing(char *line, t_info *info);

/* token */
char			**run_tokenizer(char *line, t_info *info);
int				check_sign(char *str, t_info *info);
char			**convert_env(char **arr, t_info *info);
char			*change_env_var1(char *value, char *str2, int len);
char			*convert_str(t_info *info, char *str);
char			*convert_str1(char *tmp, int *i, t_info *info);
char			*convert_str2(char *str2, int *i, t_info *info);
char			**divide_line(char *line, t_info *info);
char			**trim_quote(char **arr, t_info *info);

/* token utils */
void			check_case(char **arr, t_info *info);
int				count_arr(char **arr);
void			check_quote_flag(char c, t_info *info);
int				ft_isdoublredir(char *str);
int				ft_ispipe(char c);
int				ft_isredir(char c);
int				ft_isquote(char c);

/* lexer */
t_lex_list		*run_lexer(t_info *info);
t_lex_node		*make_lex_node(int type, char *tok);
void			add_lex_node(t_lex_list **list, t_lex_node **node);

/* lexer utils */
t_lex_list		*sort_token(t_info *info);
t_lex_node		*sort_token2(char *tok, t_info *info, int i, t_lex_list *list);
t_lex_node		*sort_token_real(char *tok);

/* parser */
t_parse_list	*run_parser(t_info *info);
void			make_parse_list(t_info *info, t_parse_list **list);
t_parse_node	*make_parse_node(t_info *info, int *count, int *node_i);
void			add_parse_node(t_parse_list **list, t_parse_node **node);

/* pipe */
int				count_parse_list(t_parse_node *p);
void			sort_pipe(t_info *info, t_parse_node *p);
void			run_no_pipe(t_parse_node *p, t_info *info);
void			run_pipe(t_info *info, t_parse_node *p);

/* pipe utils*/
void			pipe_head_node(t_info *info, t_parse_node *p);
void			pipe_middle_node(t_info *info, t_parse_node *p);
void			pipe_tail_node(t_info *info, t_parse_node *p);

/* execute */
int				run_execute(t_info *info);
void			ft_execute(t_info *info);

/* execute utils */
char			**get_path(t_env_list *list);
char			**make_cmd_arr(t_parse_node *p, t_info *info);
char			*find_cmd_path(char **arr, char *cmd);

/* env */
t_env_node		*make_env_node(char *str);
t_env_list		*make_env_list(char **envp);

/* init */
void			ft_init(int ac, char **av, t_info *info, char **envp);
void			init_info(t_info *info, char **envp);
void			sig_init(void);
void			use_arg(int ac, char **av);

/* built-in */
void			run_builtin(t_parse_node *p, t_info *info);
int				ft_isbuiltin(char *tok);
int				sort_builtin(char *cmd, t_parse_node *p, t_info *info, int i);
int				ft_unset(t_info *info, t_parse_node *p, int i);
int				ft_pwd(t_parse_node *p, t_info *info);
int				ft_env(t_info *info);
int				ft_echo(t_parse_node *p, t_info *info);

/* built-in : export */
int				ft_export(t_info *info, t_parse_node *p, int i);
void			modi_env_list(t_info *info, char **tmp);
int				ft_export_exception(char **tmp);
int				print_declare(t_env_list *list);
int				check_same(char *env, t_env_list *list);
int				check_equal(char *str);
int				find_sort(t_env_list *list, char *name);

/* redirection */
void			ft_isheredoc(t_info *info);
void			here_document(t_parse_node *p, int idx);
void			find_heredoc_p(t_parse_node *p);

/* init_term.c */
void			init_term(void);
void			set_term(void);
void			back_term(void);

/* free */
void			ft_free(char **str);
void			free_2d(char **arr);
void			free_line(t_info *info, char *line);
void			free_list(t_info *info);
void			free_info(t_info *info);

/* ft_cd */
int				is_in_env(t_env_node *env, char *args);
char			*get_env_path(t_env_node *env, const char *var);
int				ft_cd(t_parse_node *p, t_info *info);

/*ft_cd_utils.c */
int				no_env_path(void);
void			set_pwd(t_env_node *env);

/* ft_exit */
int				check_isdigit(char *str, long long num, int i);
int				ft_atoi_for_exit(char *str);
int				exit_3(int ret, t_parse_node *p);
void			exit_2(int ret, t_parse_node *p);
int				ft_exit(t_parse_node *p, t_info *info);

/*lexer_check_utils.c */
int				check_cmd_redir(t_info *info, int i, t_lex_list *lex_list);
int				ft_check_cmd(t_info *info, int i, t_lex_list *lex_list);
int				check_opt_redir(char *tok, t_info *info,
					int i, t_lex_list *lex_list);
int				ft_check_opt(char *tok, t_info *info,
					int i, t_lex_list *lex_list);

/*lexer_check_utils2.c */
int				ft_check_file(t_info *info, int i);
t_lex_node		*ft_check_inout(char *tok, t_lex_list *lex_list);

/*resdir_utils.c*/
void			in_redirection(t_info *info, int idx);
void			here_redirection(void);
void			out_redirection(t_info *info, int idx);
void			out2_redirection(t_info *info, int idx);

/*redir.c*/
void			pre_open2(t_info *info, t_lex_node	*ptr);
void			pre_open(t_info *info);
int				sort_redir(t_info *info, t_parse_node *p, int i, int in);
void			redirection(t_info *info, t_parse_node *p);

/*signal.c*/
void			signal_exit(int pid);
void			handle_signal(int signo);
void			sig_child(void);

/*sin_error.c*/
int				sin_lex(t_lex_list *lex);
int				count_marks(char *line, int i, int x, int y);
int				sin_redir(char *line, int i);
int				sin_error(char *line);

#endif
