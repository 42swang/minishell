/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:47:54 by swang             #+#    #+#             */
/*   Updated: 2022/01/19 16:58:25 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atoi_for_exit(char *str)
{
	int			i;
	long long	num;
	int minus;
	int n;

	i = 0;
	num = 0;
	minus = 1;
	n = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			minus *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (10 * num) + (str[i++] - '0');
		n++;
	}
	if ((str[i]) && !ft_isdigit(str[i]))
		return (-1);
	if (n > 19)
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
	if (info->parse_list->head != info->parse_list->tail)
		return (0);
	while (p->lex[count])
		count++;
	if (count == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (count == 2)
	{
		ret = ft_atoi_for_exit(p->cmd[1]);
		if (ret == -1)
		{
			//인자가 들어왔는데 문자거나 long long 범위 밖
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("exit: numeric argument required", 1);
			exit(255);
		}
		else
		{
			//인자가 숫자
			ft_putendl_fd("exit", 1);
			exit(ret);
		}
	}
	else
	{
		ret = ft_atoi_for_exit(p->cmd[1]);
		//인자가 여러개
		if (ret == -1)
		{
			//여러개인데 처음인자가 문자
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("exit: numeric argument required", 1);
			exit(255);
		}
		else
		{
			//여러개인데 처음인자가 숫자
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("exit: too many arguments", 1);
			return (1);
		}
	}
}
