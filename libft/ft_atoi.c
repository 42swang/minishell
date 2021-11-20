/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 02:20:52 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:05:57 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	sign;
	int	num;

	i = 0;
	minus = 1;
	sign = 0;
	num = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		sign++;
		i++;
	}
	while (ft_isdigit(str[i]))
		num = (10 * num) + (str[i++] - '0');
	if (sign > 1)
		return (0);
	return (minus * num);
}
