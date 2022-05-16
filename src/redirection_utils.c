/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:09:47 by swang             #+#    #+#             */
/*   Updated: 2022/01/23 04:06:18 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	in_redirection(t_info *info, int idx)
{
	dup2(info->file[idx], 0);
	close(info->file[idx]);
}

void	here_redirection(void)
{
	int	fd;

	fd = open("heredoc_tmp_42", O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	out_redirection(t_info *info, int idx)
{
	dup2(info->file[idx], 1);
	close(info->file[idx]);
}

void	out2_redirection(t_info *info, int idx)
{
	dup2(info->file[idx], 1);
	close(info->file[idx]);
}
