/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lex_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:03:24 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 21:08:05 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_lex_node(t_lex_list **list, t_lex_node **node)
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

t_lex_node	*make_lex_node(int type, char *tok)
{
	t_lex_node	*new;

	new = (t_lex_node *)ft_calloc(1, sizeof(t_lex_node));
	if (!new)
	{
		back_term();
		exit(0);
	}
	new->type = type;
	new->value = tok;
	return (new);
}
