/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sin_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:32:52 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 14:45:26 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_redir(t_lex_node *p)
{
	if (p->type == IN_RE || p->type == OUT_RE
		|| p->type == HEREDOC || p->type == OUT_RE2)
	{
		if (p->next == NULL)
			return (1);
		else if (p->next && (p->next->type == IN_RE || p->next->type == OUT_RE
				|| p->next->type == HEREDOC || p->next->type == OUT_RE2))
			return (1);
	}
	return (0);
}

int	sin_lex(t_lex_list *lex)
{
	if (lex->head->type == PIPE || lex->tail->type == PIPE)
		return (1);
	lex->curr = lex->head;
	while (lex->curr)
	{
		if (lex->curr->type == -1)
			return (1);
		if (lex->curr->type == PIPE)
		{
			if (lex->curr->next->type == PIPE)
				return (1);
		}
		if (check_redir(lex->curr) == 1)
			return (1);
		lex->curr = lex->curr->next;
	}
	return (0);
}

int	count_marks(char *line, int i, int x, int y)
{
	while (line && line[i])
	{
		if (line[i] == '\'')
		{
			x = 1;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] && line[i] == '\'')
				x = 0;
		}
		else if (line[i] == '\"')
		{
			y = 1;
			i++;
			while (line[i] && line[i] != '\"')
				i++;
			if (line[i] && line[i] == '\"')
				y = 0;
		}
		i++;
	}
	if ((x != 0) || (y != 0))
		return (1);
	return (0);
}

int	sin_redir(char *line, int i)
{
	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] != ' ' && (line[i + 1]))
			{
				if (line[i + 1] != line[i] || line[i + 2] != ' ')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	sin_error(char *line)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	if (count_marks(line, i, x, y) == 1)
		return (1);
	while (line[i])
	{
		if ((line[i] == '|' && ((line[i + 1]) == '\0' || (line[i + 1] != ' '))))
			return (1);
		i++;
	}
	if (sin_redir(line, i) == 1)
		return (1);
	return (0);
}
