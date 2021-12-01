/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:08:18 by swang             #+#    #+#             */
/*   Updated: 2021/11/30 15:41:49 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_info(t_info *info, char *env[])
{
	info->lex_list = 0;
	info->parse_list = 0;
	info->env_head = 0;
	info->envp = env;
	info->token = 0;
	info->quote = 0;
	info->exit_stat = 0;
	info->real = 0;
	info->path = get_path(env);
	if (info->path == NULL)
	{
		printf("Failed to find PATH in envp\n");
		exit(0); // 일단 패스경로 만드는거 에러나면 강종
	}
}


/*
void	sig_init()
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
*/