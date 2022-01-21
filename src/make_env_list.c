/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 00:17:29 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 15:53:23 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_node	*make_env_node(char *str)
{
	t_env_node	*new;

	new = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	if (new == 0)
	{
		ft_putendl_fd("Failed to make env node", 2);
		back_term();
		exit(0); // 말록실패
	}
	new->env_arr = ft_split(str, '=');
	if (new->env_arr == 0)
	{
		ft_putendl_fd("Failed to make env_arr", 2);
		back_term();
		exit(0); // 말록실패
	}
	return (new);
}

static void	add_env_node(t_env_list **list, t_env_node **node)
{
	if ((*list)->head == 0)
	{
		(*list)->head = *node;
		(*list)->curr = *node;
		(*list)->tail = *node;
	}
	else
	{
		(*list)->tail->next = *node;
		(*node)->prev = (*list)->tail;
		(*list)->tail = *node;
	}
}

t_env_list	*make_env_list(char **envp)
{
	t_env_list *list;
	t_env_node *node;
	int	i;

	i = 0;
	list = (t_env_list *)ft_calloc(1, sizeof(t_env_list));
	node = 0;
	while (envp[i])
	{
		node = make_env_node(envp[i]);
		add_env_node(&list, &node);
		i++;
	}
	return (list);
}
