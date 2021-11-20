/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:25:22 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:58:06 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	i;
	char	*str;

	if (s == 0)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	sub_len = len;
	if (ft_strlen(s + start) < len)
		sub_len = ft_strlen(s + start);
	str = ft_calloc(sub_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < sub_len)
		str[i++] = s[start++];
	return (str);
}
