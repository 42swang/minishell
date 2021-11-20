/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 23:47:57 by swang             #+#    #+#             */
/*   Updated: 2021/04/30 13:43:09 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_zero(int count)
{
	char	*str;

	str = malloc(count + 2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_plus(long long int num, int count)
{
	char	*str;

	str = malloc((size_t)count + 1);
	if (!str)
		return (NULL);
	str[count] = '\0';
	while (count >= 1)
	{
		str[count - 1] = (num % 10) + 48;
		num = num / 10;
		count--;
	}
	return (str);
}

static char	*ft_minus(long long int num, int count)
{
	char	*str;

	num = -(num);
	str = malloc((size_t)count + 2);
	if (!str)
		return (NULL);
	str[count + 1] = '\0';
	while (count >= 1)
	{
		str[count] = (num % 10) + 48;
		num = num / 10;
		count--;
	}
	str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int				count;
	long long int	c_num;
	long long int	num;

	count = 0;
	c_num = n;
	num = n;
	if (num < 0)
		c_num = (-1) * c_num;
	while (1 <= c_num)
	{
		c_num = (c_num / 10);
		count++;
	}
	if (num < 0)
		return (ft_minus(num, count));
	else if (num > 0)
		return (ft_plus(num, count));
	else
		return (ft_zero(count));
}
