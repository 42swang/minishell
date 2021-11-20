/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:41:48 by swang             #+#    #+#             */
/*   Updated: 2021/11/21 02:48:32 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotation_mark(char *str, int *i)
{
	char	quote;
	int		idx;

	idx = *i;
	quote = str[idx];
	idx++;
	//printf("cqm : %c\n", str[idx]);
	while (str[idx] != 0)
	{
		if (str[idx] == quote)
		{
			(*i) = (idx + 1); //따옴표나오면 다음인덱스로 넘겨서 내보냄
			return (0);
		}
		idx++;
	}
	printf("Error : not closed quotation mark\n");
	return (-1);
}

int	find_start_end(char *s, int *i, int *start, char c)
{
	char	quote;
	int		idx;

	idx = *i;
	while (s[idx] && s[idx] != c)
	{
		if (s[idx] == '\'' || s[idx] == '\"')
		{
			*start = idx + 1;
			quote = s[idx];
			idx++;
			while (s[idx] != quote)
				idx++;
			*i = idx + 1;
			return (idx);
		}
		else
			idx++;
	}
	*i = idx;
	return (idx);
}
