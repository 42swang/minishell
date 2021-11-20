/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 04:26:06 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:20:12 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;
	char	*new;

	len = ft_strlen(s1);
	str = (char *)s1;
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (len--)
		new[len] = str[len];
	return (new);
}
