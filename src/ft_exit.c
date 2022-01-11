/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:47:54 by swang             #+#    #+#             */
/*   Updated: 2022/01/11 18:27:53 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atoi_for_exit(char *str)
{
	int			i;
	long long	num;
	int minus;

	i = 0;
	num = 0;
	minus = 1;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		num = (10 * num) + (str[i++] - '0');
	if ((str[i]) && !ft_isdigit(str[i]))
		return (-1);
	if (minus < 0)
	{
		num %= 256;
		num = 256 - num;
	}
	else if (num > 255)
		num %= 256;
	return (num);
}

int ft_exit(t_parse_node *p, t_info *info)
{
	int count;
	int ret;

	count = 0;
	ret = 0;
	while (p->lex[count])
		count++;
//	printf("count == %d\n", count);
	if (count == 1)
	{
		//printf("count == 1\n");
		info->exit_stat = 4242;
		*(info->run_exit) = 1;
	}
	else if (count == 2)
	{
		ret = ft_atoi_for_exit(p->cmd[1]);
		if (ret == -1)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			info->exit_stat = 255;
			*(info->run_exit) = 1;
			return (255);
		}
		else
		{
			info->exit_stat = ret;
			*(info->run_exit) = 1;
		}
	}
	else
	{
		ret = ft_atoi_for_exit(p->cmd[1]);
		if (ret == -1)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			info->exit_stat = 255;
			*(info->run_exit) = 1;
			return (255);
		}
		else
		{
			ft_putendl_fd("exit", 2);
			ft_putendl_fd("exit: too many arguments", 2);
		}
	}
	//1. 뒤숫자 인자가 들어오면 그숫자를 종료값으로 반환
	//2. 문자넣으면 숫자 인자가 요구된다고 경고메세지 출력
	//3. 숫자가 여러개들어가면 투매니알규먼트
	//info->exit_stat 여기에 숫자저장
	
	return (ret);
}