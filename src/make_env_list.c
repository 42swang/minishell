/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:17:29 by swang             #+#    #+#             */
/*   Updated: 2021/11/25 21:44:16 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	make_env_node(char *str, t_info *info)
{
	t_env_node	*new;
	t_env_node	*p;

	new = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	if (!new)
		exit(0);
	new->env_arr = ft_split(str, '=');
	if (info->env_head == 0)
		info->env_head = new;
	else
	{
		p = info->env_head;
		while (p->next) //p가 널이면 멈춘다.
			p = p->next;
		p->next = new;
	}	//리스트 마지막 찾아서 = new;
	new = 0;
}

void	make_env_list(t_info *info)
{
	int	i = 0;
	while (info->envp[i])
	{
		make_env_node(info->envp[i], info);
		i++;
	}
}