/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 18:00:38 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_no_pipe_builtin(t_info *info)
{
	int	i;
	int	*ptr;

	i = 0;
	ptr = info->parse_list->head->lex;
	while (ptr[i] && ptr[i] != CMD)
		i++;
	if (ptr[i] == 0)
		return (0);
	if (info->parse_list->head == info->parse_list->tail
		&& ft_isbuiltin(info->parse_list->head->cmd[i]))
		return (1);
	else
		return (0);
}

static void	line_is_null(void)
{
	ft_putstr_fd("\x1b[1A", 1);
	ft_putstr_fd("\033[12C", 1);
	ft_putendl_fd("exit", 1);
	back_term();
	exit(0);
}

static void	run_minishell(t_info *info, char *line)
{
	if (sin_error(line))
	{
		g_glovar.g_exit_status = 258;
		ft_putendl_fd("syntax error near unexpected token", 2);
	}
	else if (parsing(line, info) == -1)
	{
		g_glovar.g_exit_status = 258;
		ft_putendl_fd("syntax error near unexpected token", 2);
	}
	else
	{
		if (check_no_pipe_builtin(info) == 1)
		{
			pre_open(info);
			ft_isheredoc(info);
			run_builtin(info->parse_list->head, info);
		}
		else
			ft_execute(info);
	}
}

static int	ft_isspace_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	char			*line;
	t_info			info;

	ft_init(argc, argv, &info, envp);
	while (42)
	{
		sig_init();
		set_term();
		line = readline("GAEPOSHELL$ ");
		if (line && *line != '\0')
			add_history(line);
		if (line == NULL)
			line_is_null();
		else if (*line == '\0' || ft_isspace_str(line) == 1)
		{
			free(line);
			line = 0;
			continue ;
		}
		run_minishell(&info, line);
		free_line(&info, line);
	}
	free_info(&info);
	return (0);
}
