/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:58:36 by swang             #+#    #+#             */
/*   Updated: 2022/01/11 18:19:18 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	export_env(char *env, t_env_list *list, int sort)
{
	t_env_node *new;
	
	new = mak
	/*
	while (sort)
		p = p->next;
	p->next = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	p->next->env_arr = ft_split(env, '=');
	p->next->next = 0;
	*/
	return (0);
}

static int	find_sort(char *env, t_env_list *list)
{
	t_env_node	*p;
	int			len;
	int			i;
	char		c;

	len = ft_strlen(env);
	i = 0;

	/*
	1. 첫글자부터 차례로 찾아서 정렬
	*/
	
	while (p)
	{
		c = p->env_arr[0][1];
		while (c < env[i])
			p = p->next;
		if (c == p->env_arr[0])
	}

}

int	ft_export(t_info *info, t_parse_node *p, int i)
{
	char *env;
	int	sort;
	int	ret;

	env = p->cmd[i + 1];
	ret = export_env(env, info->env_list, sort);
	return (ret);
}
