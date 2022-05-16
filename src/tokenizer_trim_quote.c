/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_trim_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:50:36 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 17:51:52 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*trim_quote4(char *trim, int *i, char q)
{
	char	*head;
	char	*tail;
	char	*ret;
	int		len;

	len = 0;
	while (trim[len] != q)
		len++;
	head = ft_substr(trim, 0, len);
	tail = ft_substr(trim, len + 1, ft_strlen(trim + len + 1));
	ret = ft_strjoin(head, tail);
	*i += len;
	ft_free(&head);
	ft_free(&tail);
	return (ret);
}

static char	*trim_quote3(char *str, int *i, char q, t_info *info)
{
	char	*head;
	char	*trim;
	char	*ret;

	while (info->quote & SQ || info->quote & DQ)
	{
		head = ft_substr(str, 0, *i);
		trim = trim_quote4(str + (*i) + 1, i, q);
		ret = ft_strjoin(head, trim);
		ft_free(&head);
		ft_free(&trim);
		if (info->quote & SQ)
			info->quote &= ~SQ;
		else if (info->quote & DQ)
			info->quote &= ~DQ;
	}
	return (ret);
}

static char	*trim_quote2(char *str, t_info *info)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup(str);
	while (ret[i])
	{
		check_quote_flag(ret[i], info);
		if (info->quote & SQ)
		{
			tmp = ret;
			ret = trim_quote3(ret, &i, '\'', info);
			ft_free(&tmp);
		}
		else if (info->quote & DQ)
		{
			tmp = ret;
			ret = trim_quote3(ret, &i, '\"', info);
			ft_free(&tmp);
		}
		else
			i++;
	}
	return (ret);
}

char	**trim_quote(char **arr, t_info *info)
{
	int		i;
	char	**ret;
	int		count;

	i = 0;
	count = count_arr(arr);
	ret = (char **)ft_calloc(count + 1, sizeof(char *));
	check_case(arr, info);
	while (arr[i])
	{
		ret[i] = trim_quote2(arr[i], info);
		i++;
	}
	return (ret);
}
