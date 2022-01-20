/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:00:42 by swang             #+#    #+#             */
/*   Updated: 2022/01/20 14:32:21 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
	arr = 0;
}

void	ft_free(char **str)
{
	free(*str);
	*str = 0;
}

void	free_line(t_info *info, char *line)
{
	info->quote = 0;
	if (line)
		ft_free(&line);
	if (info->real)
	{
		free(info->real);
		info->real = 0;
	}
	if (info->file)
	{
		free(info->file);
		info->file = 0;
	}
	if (info->path)
		free_2d(info->path);
	if (info->token)
		free_2d(info->token);
	if (info->cmd_arr != 0)
		free_2d(info->cmd_arr);
	free_list(info);
}
