/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:09:47 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:32:29 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pre_open2(t_info *info, t_lex_node	*ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		if (ptr->type == IN_FILE)
			info->file[i] = open(ptr->value, O_RDONLY);
		else if (ptr->type == OUT_FI)
			info->file[i] = open(ptr->value, O_RDWR | O_CREAT | O_TRUNC, 00644);
		else if (ptr->type == OUT_FI2)
			info->file[i] = open(ptr->value, O_RDWR | \
				O_CREAT | O_APPEND, 00644);
		else
			i--;
		i++;
		ptr = ptr->next;
	}
}

void	pre_open(t_info *info)
{
	int			i;
	t_lex_node	*ptr;

	i = 0;
	ptr = info->lex_list->head;
	while (ptr)
	{
		if (ptr->type == IN_FILE || ptr->type == OUT_FI || \
			ptr->type == HERE_DEL || ptr->type == OUT_FI2)
			i++;
		ptr = ptr->next;
	}
	info->file = (int *)ft_calloc(i + 1, sizeof(int));
	ptr = info->lex_list->head;
	pre_open2(info, ptr);
}

int	sort_redir(t_info *info, t_parse_node *p, int i, int in)
{
	if (p->lex[i] == IN_RE)
	{
		in_redirection(info, in);
		in++;
		return (1);
	}
	else if (p->lex[i] == HEREDOC)
	{
		here_redirection();
		return (2);
	}
	else if (p->lex[i] == OUT_RE)
		return (3);
	else if (p->lex[i] == OUT_RE2)
		return (4);
	return (0);
}

void	redirection(t_info *info, t_parse_node *p)
{
	int	i;
	int	in;
	int	out;
	int	out2;
	int	sort;

	i = 0;
	in = 0;
	out = 0;
	out2 = 0;
	while (p->lex[i])
	{
		sort = sort_redir(info, p, i++, in);
		if (sort == 3)
		{
			out_redirection(info, out);
			out++;
		}
		else if (sort == 4)
		{
			out2_redirection(info, out2);
			out2++;
		}
	}
	find_heredoc_p(p);
}
