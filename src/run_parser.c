/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:44:02 by swang             #+#    #+#             */
/*   Updated: 2021/12/01 13:22:38 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_parser(t_info *info)
{
	t_lexical_node *p;
	t_parse_list *parse;

	parse = (t_parse_list *)ft_calloc(1, sizeof(t_parse_list));
	info->parse_list = parse;
	int	i;
	int	node_i;
	i = 0;
	node_i = 0;
	p = info->lex_list->head;
	info->lex_list->curr = info->lex_list->head;
	while (p) //머리부터 탐색
	{
		if (p->type == PIPE)
		{
			make_parse_node(p, info, i, node_i); // 파이프 전까지의 데이터를 담아서
			i = -1;
			node_i++;
		} //i는 여기를 지나면서 0이 됨.
		i++;
		if (!(p->next))
			break ;
		p = p->next;
	}
	make_parse_node(p, info, i, node_i);
}

void	make_parse_node(t_lexical_node *p, t_info *info, int i, int node_i)
{
//	i는 렉서노드 개수
//	node_i는 파서인덱스
	t_parse_node *new;
	int idx;
//{ㅁ->ㅁ->ㅁ} -> | -> {ㅁ-> ㅁ->ㅁ}
	idx = 0;
	new = (t_parse_node *)ft_calloc(1, sizeof(t_parse_node));
	new->index = node_i;
	new->cmd = (char **)ft_calloc(i + 1, sizeof(char *));
	new->lex = (int *)ft_calloc(i + 1, sizeof(int));
	while (i)
	{
//		new->cmd[idx] = (char *)malloc(sizeof(char) * (ft_strlen(info->lex_list->curr->value)));
		new->cmd[idx] = info->lex_list->curr->value;
		new->lex[idx] = info->lex_list->curr->type;
		i--;
		idx++;
		info->lex_list->curr = info->lex_list->curr->next;
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
	info->lex_list->curr = p->next; //p는 파이프가 나오는 위치
	new = 0;
}
	// curr 이 가리키는 부분부터 i 개만큼 렉서 노드를 탐색
