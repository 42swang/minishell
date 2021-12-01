/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:00:42 by swang             #+#    #+#             */
/*   Updated: 2021/11/26 15:12:01 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
	arr = 0;
}

void	delete_line(t_info *info, char *line)
{
	free(line);
	line = 0;
	if (info->token)
	{
		ft_free(info->token);
		info->token = 0;
	}
	if (info->real) 
	{
		free(info->real);
		info->real = 0;
	}
	info->quote = 0;
}
	/*
		line과 관련된 애들 정보 지우기 (새 라인을 받아올거니까)
		2. 토큰 배열 초기화
		3. info 구조체중에 초기화 해야할거 초기화 해주기
			info.real 동적할당된 int배열 free
			info->token = 0; // 2차원 배열 free
			info->quote = 0; // 전부 off 시켜주자

		info->exit_stat는 종료값을 넣어줘야함
		*/