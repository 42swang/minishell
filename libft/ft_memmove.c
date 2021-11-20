/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:49 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:14:00 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*target;
	unsigned char	*source;

	target = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len--)
			target[len] = source[len];
	}
	return (dst);
}
