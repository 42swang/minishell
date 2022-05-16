/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:29:06 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 18:03:13 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*change_env_var1(char *value, char *str2, int len)
{
	char	*head;
	char	*tail;
	char	*ret;

	head = value;
	tail = ft_substr(str2 + 1, len, ft_strlen(str2 + len));
	ret = ft_strjoin(head, tail);
	free(tail);
	tail = 0;
	return (ret);
}

char	*convert_str1(char *tmp, int *i, t_info *info)
{
	char	*s1;
	char	*s2;

	s1 = ft_substr(tmp, 0, *i);
	s2 = convert_str2(tmp + *i, i, info);
	ft_free(&tmp);
	tmp = ft_strjoin(s1, s2);
	ft_free(&s1);
	ft_free(&s2);
	return (tmp);
}

int	count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	check_case(char **arr, t_info *info)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]) == 1)
		{
			if (ft_ispipe(arr[i][0]) || ft_isredir(arr[i][0]))
				info->real[i] = 1;
		}
		else if (ft_strlen(arr[i]) == 2)
		{
			if (ft_isdoublredir(arr[i]))
				info->real[i] = 1;
		}
		i++;
	}
}
