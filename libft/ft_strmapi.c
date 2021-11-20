/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:40:15 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:20:56 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	char	*s1;
	char	*str;

	if (s == 0)
		return (NULL);
	s_len = ft_strlen(s);
	s1 = (char *)s;
	str = ft_calloc(s_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s_len--)
		str[s_len] = (*f)(s_len, s1[s_len]);
	return (str);
}
