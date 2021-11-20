/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:25:00 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:21:12 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	hay_len;
	size_t	ndl_len;

	i = 0;
	hay_len = ft_strlen(haystack);
	ndl_len = ft_strlen(needle);
	if (needle == 0 || *needle == '\0' || !ndl_len)
		return ((char *)haystack);
	if (len < ndl_len || hay_len < ndl_len || !len)
		return (NULL);
	while (i + ndl_len <= len && *haystack)
	{
		if (ft_strncmp(haystack, needle, ndl_len) == 0)
			return ((char *)haystack);
		i++;
		haystack++;
	}
	return (NULL);
}
