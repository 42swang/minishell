/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:31:12 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:13:01 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*target;
	unsigned char	*source;

	target = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n--)
	{
		if (*source == (unsigned char)c)
		{
			*target++ = *source++;
			return (target);
		}
		*target++ = *source++;
	}
	return (NULL);
}
