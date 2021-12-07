/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:44:02 by swang             #+#    #+#             */
/*   Updated: 2021/12/07 14:07:43 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_parser(t_info *info)
{
	t_lexical_node *p;

	info->parse_list = (t_parse_list *)ft_calloc(1, sizeof(t_parse_list));
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
			make_parse_node(info, count, node_i); // 파이프 전까지의 데이터를 담아서
			info->lex_list->curr = p->next;
			// 파이프 다음부터 만들어야 하므로 curr은 포인터 다음의 렉서노드를 가리키고 있음
			count = 0;
			node_i++;
		} //i는 여기를 지나면서 0이 됨.
		else
			count++;
		p = p->next;
	}
	make_parse_node(info, count, node_i);
}

void	make_parse_node(t_info *info, int count, int node_i)
{
	t_parse_node *new;
	int idx;
	idx = 0;
	new = (t_parse_node *)ft_calloc(1, sizeof(t_parse_node));
	new->index = node_i;
	new->cmd = (char **)ft_calloc(count + 1, sizeof(char *));
	new->lex = (int *)ft_calloc(count + 1, sizeof(int));
	while (idx < count)
	{
		new->cmd[idx] = info->lex_list->curr->value;
		new->lex[idx] = info->lex_list->curr->type;
		idx++;
		info->lex_list->curr = info->lex_list->curr->next;
		//첫 진입시 curr은 머리, 머리부터 count개수만큼 만든다.
		//재진입시 curr은 이전 파이프의 다음노드부터 count개수만큼 (파이프와 파이프 사이를 만드는 중)
	}
	if (info->parse_list->head == 0)
	{
		info->parse_list->head = new;
		info->parse_list->tail = new;
	}
	else
	{
		info->parse_list->tail->next = new;
		new->prev = info->parse_list->tail;
		info->parse_list->tail = new;
	}
	new = 0;
}
	// curr 이 가리키는 부분부터 i 개만큼 렉서 노드를 탐색
