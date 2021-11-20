/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:25:42 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:13:54 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*target;
	unsigned char	*source;

	if (!dst && !src)
		return (dst);
	target = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n--)
		*target++ = *source++;
	return (dst);
}
