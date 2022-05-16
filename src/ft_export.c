/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:58:36 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:43:10 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_list(t_env_list **list, int sort, t_env_node **node)
{
	(*list)->curr = (*list)->head;
	if (sort == 0)
	{
		(*node)->next = (*list)->head;
		(*list)->head->prev = (*node);
		(*list)->head = *node;
	}
	else
	{
		while (sort--)
			(*list)->curr = (*list)->curr->next;
		(*list)->curr->prev->next = (*node);
		(*node)->prev = (*list)->curr->prev;
		(*list)->curr->prev = (*node);
		(*node)->next = (*list)->curr;
	}
}

static t_env_node	*make_env_node2(char **tmp)
{
	t_env_node	*new;

	new = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	if (new == 0)
	{
		ft_putendl_fd("Failed to make env node", 2);
		back_term();
		exit(0);
	}
	new->env_arr = (char **)ft_calloc(3, sizeof(char *));
	new->env_arr[0] = tmp[0];
	new->env_arr[1] = tmp[1];
	if (new->env_arr == 0)
	{
		ft_putendl_fd("Failed to make env_arr", 2);
		back_term();
		exit(0);
	}
	return (new);
}

static void	make_new(t_info *info, char **tmp)
{
	t_env_node	*new_node;
	int			sort;

	new_node = make_env_node2(tmp);
	sort = find_sort(info->env_list, new_node->env_arr[0]);
	add_list(&(info->env_list), sort, &new_node);
}

void	modi_env_list(t_info *info, char **tmp)
{
	t_env_node	*p;
	char		**be_free;

	p = info->env_list->curr;
	be_free = p->env_arr;
	p->env_arr = tmp;
	free_2d(be_free);
	be_free = 0;
}

int	ft_export(t_info *info, t_parse_node *p, int i)
{
	int		idx;
	char	*env;
	char	**tmp;

	env = p->cmd[i + 1];
	if (check_equal(env) == 0)
		return (print_declare(info->env_list));
	idx = check_equal(env);
	if (idx == 0)
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		return (1);
	}
	tmp = (char **)ft_calloc(3, sizeof(char *));
	tmp[0] = ft_substr(env, 0, idx);
	tmp[1] = ft_substr(env + idx + 1, 0, ft_strlen(env + idx + 1));
	if (ft_export_exception(tmp) == -1)
		return (1);
	if (check_same(tmp[0], info->env_list))
		modi_env_list(info, tmp);
	else
		make_new(info, tmp);
	return (0);
}
