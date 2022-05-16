/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:09:47 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 14:59:47 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_file(t_info *info, int i)
{
	if (i > 0 && info->real[i - 1] == 1)
	{
		if (info->token[i - 1][0] == '<' || info->token[i - 1][0] == '>')
			return (1);
		else
			return (0);
	}
	return (0);
}

t_lex_node	*ft_check_inout(char *tok, t_lex_list *lex_list)
{
	t_lex_node	*node;

	node = 0;
	if (lex_list->tail->type == IN_RE)
		node = make_lex_node(IN_FILE, tok);
	else if (lex_list->tail->type == OUT_RE)
		node = make_lex_node(OUT_FI, tok);
	else if (lex_list->tail->type == HEREDOC)
		node = make_lex_node(HERE_DEL, tok);
	else if (lex_list->tail->type == OUT_RE2)
		node = make_lex_node(OUT_FI2, tok);
	return (node);
}
