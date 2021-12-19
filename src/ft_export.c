/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:58:36 by swang             #+#    #+#             */
/*   Updated: 2021/12/20 02:08:05 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	export_env(char *env, t_env_node *p)
{
	while (p->next)
		p = p->next;
	p->next = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	p->next->env_arr = ft_split(env, '=');
	p->next->next = 0;
	return (0);
}

int	ft_export(t_info *info, t_parse_node *p, int i)
{
	char	*env;
	int	ret;

	env = p->cmd[i + 1];
	printf("	%s\n", p->cmd[i + 1]);
	ret = export_env(env, info->env_head);
	return (ret);
}
