/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:03:24 by swang             #+#    #+#             */
/*   Updated: 2021/12/06 23:54:24 by swang            ###   ########.fr       */
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
	{
		return(0);
		printf("in isbuiltin\n");
	}
}

void	make_lex_node(int type, t_info *info, char *tok)
{
	t_lexical_node *new;

	new = (t_lexical_node *)ft_calloc(1, sizeof(t_lexical_node));
	if (!new)
		exit(0); //임시로 탈출
	new->type = type;
	new->value = tok;
	if (info->lex_list->head == 0)
	{
		info->lex_list->head = new;
		info->lex_list->tail = new;
	}
	else
	{
		info->lex_list->tail->next = new;
		new->prev = info->lex_list->tail;
		info->lex_list->tail = new;
	}
	new = 0;
}

void	sort_token(t_info *info)
{
	int		i;
	char	*tok;
	//빌트인 함수 이외에도 명령어 취급 해야함
	i = 0;
	while (info->token[i])
	{
		tok = info->token[i];
		if (info->real[i] == 1)
		{
			if (tok[0] == '|')
				make_lex_node(PIPE, info, tok);
			else if (ft_strncmp(tok, ">>", 2) == 0)
				make_lex_node(OUT_RE2, info, tok);
			else if (ft_strncmp(tok, "<<", 2) == 0)
				make_lex_node(HEREDOC, info, tok);
			else if (tok[0] == '>')
				make_lex_node(OUT_RE, info, tok);
			else if (tok[0] == '<')
				make_lex_node(IN_RE, info, tok);
		}
		else if (ft_check_file(info, i) == 1)
			ft_check_inout(info, tok);
		else if (ft_check_cmd(info, i) == 1)
			make_lex_node(CMD, info, tok);
		else if (ft_check_opt(tok, info, i) == 1)
			make_lex_node(OPT, info, tok);
		else
			make_lex_node(ARG, info, tok);
		i++;
	}
}

void run_lexer(t_info *info)
{
	info->lex_list = (t_lexical_list *)ft_calloc(1, sizeof(t_lexical_list));
	sort_token(info);
}

void init_lex(t_lexical_list *lex)
{
	lex->head = 0;
	lex->curr = 0;
	lex->tail = 0;
}