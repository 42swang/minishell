/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:44:02 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 20:26:17 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_parse_node(t_parse_list **list, t_parse_node **node)
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

t_parse_node	*make_parse_node(t_info *info, int *count, int *node_i)
{
	t_parse_node	*new;
	int				idx;

	idx = 0;
	new = (t_parse_node *)ft_calloc(1, sizeof(t_parse_node));
	new->index = *node_i;
	new->cmd = (char **)ft_calloc(*count + 1, sizeof(char *));
	new->lex = (int *)ft_calloc(*count + 1, sizeof(int));
	while (idx < *count)
	{
		new->cmd[idx] = info->lex_list->curr->value;
		new->lex[idx] = info->lex_list->curr->type;
		idx++;
		info->lex_list->curr = info->lex_list->curr->next;
	}
	*count = 0;
	(*node_i)++;
	return (new);
}

void	make_parse_list(t_info *info, t_parse_list **list)
{
	t_parse_node	*node;
	t_lex_node		*p;
	int				count;
	int				node_i;

	count = 0;
	node_i = 0;
	p = info->lex_list->head;
	info->lex_list->curr = info->lex_list->head;
	while (p)
	{
		if (p->type == PIPE)
		{
			node = make_parse_node(info, &count, &node_i);
			info->lex_list->curr = p->next;
			add_parse_node(list, &node);
		}
		else
			count++;
		p = p->next;
	}
	node = make_parse_node(info, &count, &node_i);
	add_parse_node(list, &node);
}

t_parse_list	*run_parser(t_info *info)
{
	t_parse_list	*list;

	list = (t_parse_list *)ft_calloc(1, sizeof(t_parse_list));
	make_parse_list(info, &list);
	return (list);
}
