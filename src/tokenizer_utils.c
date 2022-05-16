/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:08:55 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 20:45:32 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	ft_isredir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	ft_ispipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int	ft_isdoublredir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<' && str[i])
				return (1);
		}
		else if (str[i] == '>')
		{
			i++;
			if (str[i] == '>' && str[i])
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	check_quote_flag(char c, t_info *info)
{
	if (c == '\'' && !(info->quote & SQ + DQ))
		info->quote |= SQ;
	else if (c == '\"' && !(info->quote & SQ + DQ))
		info->quote |= DQ;
	else if (c == '\'' && info->quote & SQ)
		info->quote &= ~SQ;
	else if (c == '\"' && info->quote & DQ)
		info->quote &= ~DQ;
}
