/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:47:54 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 18:18:37 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_isdigit(char *str, long long num, int i)
{
	int	n;

	n = 0;
	if (str[i] == '\0')
		return (-1);
	while (ft_isdigit(str[i]))
	{
		num = (10 * num) + (str[i++] - '0');
		n++;
	}
	if ((str[i]) && !ft_isdigit(str[i]))
		return (-1);
	if (n > 19)
		return (-1);
	return (num);
}

int	ft_atoi_for_exit(char *str)
{
	int			i;
	long long	num;
	int			minus;

	i = 0;
	num = 0;
	minus = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			minus *= -1;
		i++;
	}
	num = check_isdigit(str, num, i);
	if (num == -1)
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

int	exit_3(int ret, t_parse_node *p)
{
	ret = ft_atoi_for_exit(p->cmd[1]);
	if (ret == -1)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("exit: numeric argument required", 2);
		back_term();
		exit(255);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	return (0);
}

void	exit_2(int ret, t_parse_node *p)
{
	ret = ft_atoi_for_exit(p->cmd[1]);
	if (ret == -1)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("exit: numeric argument required", 2);
		back_term();
		exit(255);
	}
	else
	{
		ft_putendl_fd("exit", 2);
		back_term();
		exit(ret);
	}
}

int	ft_exit(t_parse_node *p, t_info *info)
{
	int	count;
	int	ret;

	count = 0;
	ret = 0;
	if (info->parse_list->head != info->parse_list->tail)
		return (0);
	while (p->lex[count])
		count++;
	if (count == 1)
	{
		ft_putendl_fd("exit", 2);
		back_term();
		exit(0);
	}
	else if (count == 2)
		exit_2(ret, p);
	else
		return (exit_3(ret, p));
	return (0);
}
