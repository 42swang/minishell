/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:19:21 by swang             #+#    #+#             */
/*   Updated: 2022/01/23 04:06:18 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cmd_redir(t_info *info, int i, t_lex_list *lex_list)
{
	while (lex_list->curr && 199 < lex_list->curr->type && \
		lex_list->curr->type < 502)
	{
		lex_list->curr = lex_list->curr->prev;
	}
	if (lex_list->curr && lex_list->curr->type == PIPE)
	{
		info->real[i] = 2;
		return (1);
	}
	else if (lex_list->curr == 0)
	{
		info->real[i] = 2;
		return (1);
	}
	else
		return (0);
}

int	ft_check_cmd(t_info *info, int i, t_lex_list *lex_list)
{
	if (i == 0)
	{
		info->real[i] = 2;
		return (1);
	}
	lex_list->curr = lex_list->tail;
	if (i > 0 && info->token[i - 1][0] == '|')
	{
		info->real[i] = 2;
		return (1);
	}
	else if (199 < lex_list->curr->type && lex_list->curr->type < 502)
		return (check_cmd_redir(info, i, lex_list));
	else
		return (0);
}

int	check_opt_redir(char *tok, t_info *info, int i, t_lex_list *lex_list)
{
	while (lex_list->curr && 199 < lex_list->curr->type && \
		lex_list->curr->type < 502)
		lex_list->curr = lex_list->curr->prev;
	if (lex_list->curr && (lex_list->curr->type == CMD || \
		lex_list->curr->type == OPT))
	{
		if (*tok == '-')
		{
			info->real[i] = 3;
			return (1);
		}
		return (0);
	}
	return (0);
}

int	ft_check_opt(char *tok, t_info *info, int i, t_lex_list *lex_list)
{
	if (i == 0)
		return (0);
	lex_list->curr = lex_list->tail;
	if (i > 0 && (info->real[i - 1] == 2 || info->real[i - 1] == 3))
	{
		if (*tok == '-')
		{
			info->real[i] = 3;
			return (1);
		}
		return (0);
	}
	else if (lex_list->curr->type && 199 < lex_list->curr->type && \
		lex_list->curr->type < 502)
		return (check_opt_redir(tok, info, i, lex_list));
	else
		return (0);
}
