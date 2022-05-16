/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:02:49 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:58:45 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	unset_env2(t_env_list **list, t_env_node **p)
{
	if ((*p) == (*list)->head)
	{
		(*list)->head = (*p)->next;
		(*list)->head->prev = 0;
	}
	else if ((*p) == (*list)->tail)
	{
		(*list)->tail = (*p)->prev;
		(*list)->tail->next = 0;
	}
	else
	{
		(*p)->prev->next = (*p)->next;
		(*p)->next->prev = (*p)->prev;
	}
}

static int	unset_env(char *env, t_env_list *list)
{
	t_env_node	*p;

	p = list->head;
	while (p)
	{
		if (ft_strncmp(env, p->env_arr[0], ft_strlen(p->env_arr[0]) + 1) == 0)
			break ;
		p = p->next;
	}
	if (p == NULL)
		return (0);
	unset_env2(&list, &p);
	free(p->env_arr[0]);
	p->env_arr[0] = 0;
	free(p->env_arr[1]);
	p->env_arr[1] = 0;
	free(p->env_arr);
	p->env_arr = 0;
	free(p);
	p = 0;
	return (0);
}

int	ft_unset(t_info *info, t_parse_node *p, int i)
{
	char	*env;
	int		ret;

	env = p->cmd[i + 1];
	if (env == 0)
		return (0);
	ret = unset_env(env, info->env_list);
	return (ret);
}
