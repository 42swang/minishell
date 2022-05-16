/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:57:25 by swang             #+#    #+#             */
/*   Updated: 2022/01/23 22:02:02 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_idx(char *old, char *new)
{
	char	c_old;
	char	c_new;

	c_old = *old;
	c_new = ft_toupper(*new);
	if (c_old > c_new)
		return (1);
	else if (c_old == c_new)
		return (0);
	else
		return (-1);
}

int	find_sort(t_env_list *list, char *name)
{
	t_env_node	*p;
	int			count;
	int			idx;

	p = list->head;
	idx = 0;
	count = 0;
	while (p)
	{
		if (find_idx(p->env_arr[0], name) == -1)
		{
			p = p->next;
			count++;
		}
		else
			break ;
	}
	return (count);
}

int	check_same(char *env, t_env_list *list)
{
	t_env_node	*p;

	p = list->head;
	while (p)
	{
		if (ft_strncmp(env, p->env_arr[0], ft_strlen(env) + 1) == 0)
		{
			list->curr = p;
			return (1);
		}
		p = p->next;
	}
	return (0);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
