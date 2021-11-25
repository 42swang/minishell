/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:08:55 by swang             #+#    #+#             */
/*   Updated: 2021/11/25 22:06:31 by swang            ###   ########.fr       */
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
	if (c == '\'' && !(info->quote & SQ + DQ)) // sq와 dq가 꺼져있는데 sq 등장시 on (sq가 켜져있으면 꺼야하고 dq가 켜져있으면 sq는 문자취급되어야함(켜면안됨))
		info->quote |= SQ;
	else if(c == '\"' && !(info->quote & SQ + DQ))
		info->quote |= DQ;
	else if (c == '\'' && info->quote & SQ) //켜져있음 끈다
		info->quote &= ~SQ;
	else if (c == '\"' && info->quote & DQ)
		info->quote &= ~DQ;
}