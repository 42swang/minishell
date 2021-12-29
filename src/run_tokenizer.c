/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:59:22 by swang             #+#    #+#             */
/*   Updated: 2021/12/24 19:22:49 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_sign(char *str, t_info *info)
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
	char	**devide;
	char	**convert;
	char	**ret;
	int		i;

	i = 0;
	ret = 0;
	devide = 0;
	convert = 0;
	devide = divide_line(line, info);
	convert = convert_env(devide, info);
	ret = trim_quote(convert, info);
	free_2d(devide);
	free_2d(convert);

	return (ret);
}
