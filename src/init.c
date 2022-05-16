/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:08:18 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:31:08 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	use_arg(int ac, char **av)
{
	(void)ac;
	(void)av;
}

void	init_info(t_info *info, char **envp)
{
	info->exit_stat = 0;
	info->envp = envp;
	info->file_idx = 0;
	info->real = 0;
	info->file = 0;
	info->path = 0;
	info->token = 0;
	info->cmd_arr = 0;
	info->quote = 0;
	info->env_list = 0;
	info->lex_list = 0;
	info->parse_list = 0;
	info->env_list = make_env_list(envp);
	info->old_pwd = get_env_path(info->env_list->head, "OLDPWD");
	info->home = get_env_path(info->env_list->head, "HOME");
}

void	sig_init(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

void	ft_init(int ac, char **av, t_info *info, char **envp)
{
	g_glovar.g_exit_status = 0;
	init_term();
	use_arg(ac, av);
	init_info(info, envp);
}
