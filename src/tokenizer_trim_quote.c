/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_trim_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:50:36 by swang             #+#    #+#             */
/*   Updated: 2021/11/25 22:08:21 by swang            ###   ########.fr       */
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
}

static void	trim_quote2(char **str, int *j, char c, t_info *info)
{
	char	*line;
	char	*temp;
	char	*s1;
	char	*s2;
	int		jj;

	line = *str;
	jj = *j;
	while (info->quote & SQ || info->quote & DQ)
	{
		//line[jj] = 여는 따옴표
		s1 = ft_substr(line , 0, jj);
		// 따옴표 전까지 문자열하나 만들어준다
		s2 = trim_quote3(line + jj + 1, c, &jj);
		// s2는 여는 따옴표 다음인덱스부터 시작해서 따옴표를 제거하고 이어서 문자열의 끝까지 문자열을 만들어준다.
		temp = *str;
		*str = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
		free(temp);
		if (info->quote & SQ)
			info->quote &= ~SQ;
		else if (info->quote & DQ)
			info->quote &= ~DQ;
	}
	*j = jj;
	// 이제 jj는 어디를 가리키고 있어야 하는가? 따옴표 바로 다음 문자의 "바뀐문자열에서 위치"
	//j 의 인덱스를 jj가 그대로 받아서 이동시켰기 떄문에 더하지않고 jj값을 그냥 넣어줌
}

void	trim_quote(char **arr, t_info *info)
{
	// 가장 바깥쪽 따옴표 제거. {>} {<} {>>} {<<} 일 때는 인트배열에 참인지 기록하기 
	int	i;
	int	j;

	i = 0;
	check_case(arr, info);
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			check_quote_flag(arr[i][j], info);
			if (info->quote & SQ)
				trim_quote2(&arr[i], &j, '\'', info);
			else if (info->quote & DQ)
				trim_quote2(&arr[i], &j, '\"', info);
			else
				j++;
		}
		i++;
	}
}
