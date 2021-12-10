/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:59:22 by swang             #+#    #+#             */
/*   Updated: 2021/12/10 18:55:29 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_sign(char *str, t_info *info)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quote_flag(str[i], info);
		if (!(info->quote & SQ) && str[i] == '$')
			return (1); //치환해야하는거 하나라도 있음
		i++;
	}
	return (0);
}

char	**run_tokenizer(char *line, t_info *info)
{
	char	**arr;
	char	*tmp;
	int		i;

	i = 0;
	arr = divide_line(line, info);
	while(arr[i])
	{
		if (check_sign(arr[i], info) == 1)
		{
			tmp = arr[i];
			arr[i] = convert_env(arr[i], info);
			free(tmp);
		}
	}
	//arr = trim_quote(arr, info);
	return (arr);
}
