/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 00:37:20 by swang             #+#    #+#             */
/*   Updated: 2021/12/20 01:53:20 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_env(t_env_node *head)
{
	t_env_node *p;

	p = head;
	if (p == NULL)
		return (1); //실행 실패?
	while (p)
	{
		printf("%s=%s\n", p->env_arr[0], p->env_arr[1]);
		p = p->next;
	}
	return (0); //함수 실행성공
}

int	ft_env(t_info *info)
{
	int	ret;
	//환경변수 출력

	ret = print_env(info->env_head);
	return (ret);
}