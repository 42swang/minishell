/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:25:24 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:55:30 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_lex(t_lex_list *list)
{
	t_lex_node	*p;

	p = list->head;
	list->curr = p;
	while (p != 0)
	{
		list->curr = p->next;
		free(p);
		p = 0;
		p = list->curr;
	}
}

static void	free_parse(t_parse_list *list)
{
	t_parse_node	*p;

	p = list->head;
	list->curr = p;
	while (p != 0)
	{
		list->curr = p->next;
		free(p->cmd);
		p->cmd = 0;
		free(p->lex);
		p->lex = 0;
		free(p);
		p = 0;
		p = list->curr;
	}
}

void	free_list(t_info *info)
{
	if (info->lex_list != 0)
	{
		free_lex(info->lex_list);
		free(info->lex_list);
		info->lex_list = 0;
	}
	if (info->parse_list != 0)
	{
		free_parse(info->parse_list);
		free(info->parse_list);
		info->parse_list = 0;
	}
}

static void	free_env(t_env_list *list)
{
	t_env_node	*p;

	p = list->head;
	list->curr = p;
	while (p)
	{
		list->curr = p->next;
		free_2d(p->env_arr);
		p->env_arr = 0;
		free(p);
		p = 0;
		p = list->curr;
	}
}

void	free_info(t_info *info)
{
	if (info->env_list != 0)
	{
		free_env(info->env_list);
		free(info->env_list);
		info->env_list = 0;
	}
	if (info->old_pwd != 0)
	{
		free(info->old_pwd);
		info->old_pwd = 0;
	}
	if (info->home != 0)
	{
		free(info->home);
		info->home = 0;
	}
	info->envp = 0;
}
