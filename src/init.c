/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:08:18 by swang             #+#    #+#             */
/*   Updated: 2021/12/10 15:40:57 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_info(t_info *info)
{
	info->exit_stat = 0;
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
}

/*
void	sig_init()
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
*/
