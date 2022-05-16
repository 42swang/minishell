/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:00:42 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:53:54 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
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
	if (line != 0)
		ft_free(&line);
	if (info->real != 0)
		free(info->real);
	if (info->file != 0)
		free(info->file);
	if (info->path != 0)
		free_2d(info->path);
	if (info->token != 0)
		free_2d(info->token);
	if (info->cmd_arr != 0)
		free_2d(info->cmd_arr);
	info->real = 0;
	info->file = 0;
	info->path = 0;
	info->token = 0;
	info->cmd_arr = 0;
	free_list(info);
}
