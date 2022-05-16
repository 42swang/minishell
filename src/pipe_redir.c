/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:10:09 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 20:20:36 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_head_node(t_info *info, t_parse_node *p)
{
	int	i;

	i = 0;
	dup2(p->p_fd[1], 1);
	close(p->p_fd[1]);
	close(p->p_fd[0]);
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) == 1)
		run_builtin(p, info);
	else
		run_no_pipe(p, info);
	exit(0);
}

void	pipe_middle_node(t_info *info, t_parse_node *p)
{
	int	i;

	i = 0;
	dup2(p->prev->p_fd[0], 0);
	dup2(p->p_fd[1], 1);
	close(p->p_fd[0]);
	close(p->p_fd[1]);
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) == 1)
		run_builtin(p, info);
	else
		run_no_pipe(p, info);
}

void	pipe_tail_node(t_info *info, t_parse_node *p)
{
	int	i;

	dup2(p->prev->p_fd[0], 0);
	close(p->p_fd[0]);
	close(p->p_fd[1]);
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) == 1)
		run_builtin(p, info);
	else
		run_no_pipe(p, info);
	exit(0);
}
