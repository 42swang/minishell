/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 00:17:58 by swang             #+#    #+#             */
/*   Updated: 2021/02/03 00:33:43 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int	nbr;
	long long int	a;

	nbr = n;
	a = 0;
	if (nbr < 0)
	{
		nbr = (-1) * nbr;
		write(fd, "-", 1);
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		a = nbr % 10;
		ft_putchar_fd(a + 48, fd);
	}
	else
		ft_putchar_fd(nbr + 48, fd);
}
