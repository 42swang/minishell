/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:34:09 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:21:48 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trim_check(char c, const char *set)
{
	char	*str;

	str = (char *)set;
	if (c == 0)
		return (0);
	while (*str != c)
	{
		if (*str == 0)
			return (0);
		str++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (s1 == 0)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_trim_check(s1[start], set))
		start++;
	while (start <= end)
	{
		if (!ft_trim_check(s1[end], set))
			break ;
		end--;
	}
	return (ft_substr(s1, (unsigned int)start, (size_t)(end - start + 1)));
}
