/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:02:49 by swang             #+#    #+#             */
/*   Updated: 2022/01/20 16:47:46 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	unset_env(char *env, t_env_list *list)
{
	t_env_node *p;

	p = list->head;
	while (p)
	{
		if (ft_strncmp(env, p->env_arr[0], ft_strlen(p->env_arr[0])) == 0)
			break ;
		p = p->next;
	}
	if (p == NULL)
		return (0);
	if (p == list->head)
	{
		list->head = p->next;
		list->head->prev = 0;
	}
	else if (p == list->tail)
	{
		list->tail = p->prev;
		list->tail->next = 0;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev= p->prev;
	}
	free(p->env_arr[0]);
	free(p->env_arr[1]);
	free(p->env_arr);
	free(p);
	return (0);
}

int	ft_unset(t_info *info, t_parse_node *p, int i)
{
	//환경변수 제거
	char	*env;
	int	ret;

	env = p->cmd[i + 1];
	ret = unset_env(env, info->env_list);
	return (ret);
}
