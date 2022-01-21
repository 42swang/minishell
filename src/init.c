/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:08:18 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 13:58:24 by swang            ###   ########.fr       */
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
	info->heredoc = 0;
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

void	init_term(void)
{
	tcgetattr(0, &(glovar.origin_term));
	tcgetattr(0, &(glovar.gaepo_term));
}

void	set_term(void)
{
	glovar.gaepo_term.c_lflag &= ECHO; // 끄는건 물결에 &연산인데 이건 뭐지
	glovar.gaepo_term.c_cc[VMIN] = 1;	// 최소 입력 버퍼 크기
	glovar.gaepo_term.c_cc[VTIME] = 0; // 타이머가 0이면 무한기다림, 타이머가 작동하지않음
	tcsetattr(0, TCSANOW, &(glovar.gaepo_term));
}

void	back_term(void)
{
	tcsetattr(0, TCSANOW, &(glovar.origin_term));
}

void	sig_init(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
