/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:44:02 by swang             #+#    #+#             */
/*   Updated: 2021/12/24 19:23:32 by swang            ###   ########.fr       */
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
	t_parse_node *new;
	int idx;
	
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
		//첫 진입시 curr은 머리, 머리부터 count개수만큼 만든다.
		//재진입시 curr은 이전 파이프의 다음노드부터 count개수만큼 (파이프와 파이프 사이를 만드는 중)
	}
	*count = 0; //개수 초기화
	(*node_i)++;
	return (new);
}

void	make_parse_list(t_info *info, t_parse_list **list)
{
	t_parse_node	*node;
	t_lex_node *p;
	int	count;
	int	node_i;

	count = 0;
	node_i = 0;
	p = info->lex_list->head;
	info->lex_list->curr = info->lex_list->head;
	while (p) //머리부터 탐색
	{
		if (p->type == PIPE)
		{
			node = make_parse_node(info, &count, &node_i); // 파이프 전까지의 데이터를 담아서
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
