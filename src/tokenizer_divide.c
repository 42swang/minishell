/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_divide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:53:19 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 17:52:15 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_quote(char *line, int i)
{
	int		idx;
	char	quote;

	idx = i;
	quote = line[idx];
	idx++;
	while (line[idx] != quote && line[idx])
		idx++;
	idx++;
	return (idx);
}

static int	count_token(char *line)
{
	int		idx;
	int		count;

	idx = 0;
	count = 0;
	while (line[idx])
	{
		while (line[idx] == ' ')
			idx++;
		if (line[idx] != ' ' && line[idx])
			count++;
		while (line[idx] != ' ' && line[idx])
		{
			if (line[idx] == '\'' || line[idx] == '\"')
				idx = skip_quote(line, idx);
			else
				idx++;
		}
	}
	return (count);
}

static void	find_start_end(char *line, int *start, int *end)
{
	int	idx;

	if (*end != 0)
		idx = *end;
	else
		idx = 0;
	while (line[idx])
	{
		while (line[idx] == ' ')
			idx++;
		*start = idx;
		while (line[idx] != ' ' && line[idx])
		{
			if (line[idx] == '\'' || line[idx] == '\"')
				idx = skip_quote(line, idx);
			else
				idx++;
		}
		*end = idx;
		break ;
	}
}

static void	make_token_arr(char *line, int count, char **arr)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < count)
	{
		find_start_end(line, &start, &end);
		arr[i] = ft_substr(line, start, end - start);
		i++;
	}
}

char	**divide_line(char *line, t_info *info)
{
	char	**arr;
	int		count;

	count = count_token(line);
	info->real = (int *)ft_calloc(count + 1, sizeof(int));
	arr = (char **)ft_calloc(count + 1, sizeof(char *));
	make_token_arr(line, count, arr);
	return (arr);
}
