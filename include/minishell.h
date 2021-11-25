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

#endif








