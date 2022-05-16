/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 00:37:20 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 16:55:06 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_env(t_env_list *list)
{
	t_env_node	*p;

	p = list->head;
	if (p == NULL)
		return (1);
	while (p)
	{
		printf("%s=%s\n", p->env_arr[0], p->env_arr[1]);
		p = p->next;
	}
	return (0);
}

int	ft_env(t_info *info)
{
	int	ret;

	ret = print_env(info->env_list);
	return (ret);
}
