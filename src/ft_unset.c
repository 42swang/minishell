/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:02:49 by swang             #+#    #+#             */
/*   Updated: 2021/12/20 02:53:44 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	unset_env(char *env, t_env_node *p)
{
	//리스트 하나 제거
	//환경변수 리스트 이중연결리스트로 변경할까?
	t_env_node *head;
	t_env_node *tmp;

	int count;
	count = 0;
	head = p;
	while (p)
	{
		if (ft_strncmp(env, p->env_arr[0], ft_strlen(p->env_arr[0])) == 0)
			break ;
		else
		{
			p = p->next;
			count++;
		}
	}
	p = head;
	while (count > 1)
	{
		p = p->next;
		count--;
	}
	tmp = p->next;
	if (p->next->next != NULL)
		p->next = p->next->next;
	else
		p->next = NULL;
	free(tmp->env_arr[0]);
	free(tmp->env_arr[1]);
	free(tmp);
	return (0);
}

int	ft_unset(t_info *info, t_parse_node *p, int i)
{
	//환경변수 제거
	char	*env;
	int	ret;
	
	env = p->cmd[i + 1];
	ret = unset_env(env, info->env_head);
	return (ret);
}