/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:36:19 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 14:43:25 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_execute(t_info *info)
{
	t_parse_node	*p;
	int				i;

	p = info->parse_list->head;
	i = 0;
	ft_isheredoc(info);
	while (p->lex[i] && p->lex[i] != CMD)
		i++;
	if (p->lex[i] == 0)
		i = 0;
	if (ft_isbuiltin(p->cmd[i]) && !(p->next))
		run_builtin(p, info);
	else
	{
		if (!(p->next))
			run_no_pipe(p, info);
		else
			run_pipe(info, p);
	}
	return (g_glovar.g_exit_status);
}

void	ft_execute(t_info *info)
{
	int	pid;
	int	status;
	int	ret_child;

	status = 0;
	sig_child();
	pid = fork();
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		pre_open(info);
		ret_child = run_execute(info);
		exit(ret_child);
	}
	else
	{
		wait(&status);
		g_glovar.g_exit_status = (status >> 8);
	}
}
