/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_trim_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:50:36 by swang             #+#    #+#             */
/*   Updated: 2021/12/24 06:46:10 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_case(char **arr, t_info *info)
{
	int	i;
	
	i = 0;
	//{>} {>>} {<} {<<} 일때만 1 ><랑 <>랑 ||는 신택스에러에서 거름
	while (arr[i])
	{
		if (ft_strlen(arr[i]) == 1)
		{
			if (ft_ispipe(arr[i][0]) || ft_isredir(arr[i][0]))
				info->real[i] = 1;
		}
		else if (ft_strlen(arr[i]) == 2)
		{
			if (ft_isdoublredir(arr[i]))
				info->real[i] = 1;
		}
		i++;
	}
}

/*
static char	*trim_quote3(char *str, char c, int *jj)
{
	int		jjj;
	char	*s1;
	char	*s2;
	char	*ret;

	jjj = 0;
	while (str[jjj] != c)
		jjj++;
	// ㄴ다시 따옴표가 나올때까지 jjj를 증가시켜준다 str[jjj] == 닫는 따옴표
	s1 = ft_substr(str, 0, jjj);
	// ㄴ여는 따옴표의 다음부터 닫는 따옴표 전까지 문자열을 만들어준다
	s2 = ft_substr(str + jjj + 1, 0, ft_strlen(str + jjj + 1));
	// ㄴ닫는 따옴표의 다음인덱스부터 문자열 끝까지 만들어준다.
	ret = ft_strjoin(s1, s2);
	*jj += jjj;
	//여기 보낼때 포인터를 jj만큼 이동시켜서 보냈기 떄문에 움직인만큼 인덱스를 더해줘야함
	free(s1);
	free(s2);
	return (ret); 
}*/

static char	*trim_quote4(char *trim, int *i, char q)
{
	char	*head;
	char	*tail;
	char	*ret;
	int	len;

	len = 0;
	while (trim[len] != q)
		len++;
	// trim[len] = q;
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
		head = ft_substr(str , 0, *i);
		// 따옴표 전까지 문자열
		trim = trim_quote4(str + (*i) + 1, i, q);
		//따옴표 바로 다음 문자부터 이어지는 문자열
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
	int	i;
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
	// 가장 바깥쪽 따옴표 제거. {>} {<} {>>} {<<} 일 때는 인트배열에 참인지 기록하기 
	int	i;
	char	**ret;
	int	count;

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
