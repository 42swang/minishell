/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:03:24 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 15:53:25 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isbuiltin(char *tok)
{
	if (ft_strncmp(tok, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tok, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tok, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(tok, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(tok, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(tok, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(tok, "exit", 5) == 0)
		return (1);
	else
		return(0);
}

static void	add_lex_node(t_lex_list **list, t_lex_node **node)
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
	t_lex_node *new;

	new = (t_lex_node *)ft_calloc(1, sizeof(t_lex_node));
	if (!new)
	{
		back_term();
		exit(0); //임시로 탈출}
	}
	new->type = type;
	new->value = tok;
	return (new);
}

t_lex_node	*sort_token_real(char *tok)
{
	//real = 1일 때.
	t_lex_node	*node;

	node = 0;
	if (ft_strncmp(tok, "|", 2) == 0)
		node = make_lex_node(PIPE, tok);
	else if (ft_strncmp(tok, ">>", 3) == 0)
		node = make_lex_node(OUT_RE2, tok);
	else if (ft_strncmp(tok, "<<", 3) == 0)
		node = make_lex_node(HEREDOC, tok);
	else if (ft_strncmp(tok, ">", 2) == 0)
		node = make_lex_node(OUT_RE, tok);
	else if (ft_strncmp(tok, "<", 2) == 0)
		node = make_lex_node(IN_RE, tok);
	return (node);
}

t_lex_node	*sort_token2(char *tok, t_info *info, int i, t_lex_list *list)
{
	t_lex_node	*node;

	node = 0;
	if (ft_check_file(info, i) == 1)
		node = ft_check_inout(tok, list);
	else if (ft_check_cmd(info, i, list) == 1)
		node = make_lex_node(CMD, tok);
	else if (ft_check_opt(tok, info, i, list) == 1)
		node = make_lex_node(OPT, tok);
	else
		node = make_lex_node(ARG, tok);
	return (node);
}

t_lex_list	*sort_token(t_info *info)
{
	t_lex_list	*list;
	t_lex_node	*node;
	int		i;
	char	*tok;

	i = 0;
	list = (t_lex_list *)ft_calloc(1, sizeof(t_lex_list));
	node = 0;
	while (info->token[i])
	{
		tok = info->token[i];
		if (info->real[i] == 1)
			node = sort_token_real(tok);
		else
			node = sort_token2(tok, info, i, list);
		add_lex_node(&list, &node);
		i++;
	}
	return (list);
}

t_lex_list *run_lexer(t_info *info)
{
	t_lex_list *p;

	p = sort_token(info);
	return (p);
}
