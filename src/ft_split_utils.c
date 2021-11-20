/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:41:48 by swang             #+#    #+#             */
/*   Updated: 2021/11/20 23:01:14 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotation_mark(char *str, int *i)
{
	char	c;
	int		idx;

	idx = *i;
	c = *str;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
		{
			(*i) += idx + 1;
			return (0);
		}
		(*i)++;
	}
	printf("Error\nnot closed quotation mark\n");
	return (-1);
}

int	find_start_end(char *s, int *i, int *start, char c)
{
	char	quote;

	while (s[*i] && s[*i] != c)
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			*start = *i + 1;
			quote = s[*i];
			(*i)++;
			while (s[*i] != quote)
				(*i)++;
			return (*i);
		}
		else
			(*i)++;
	}
	return (*i);
}
