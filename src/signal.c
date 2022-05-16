/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:33:42 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:27:06 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_exit(int pid)
{
	if (pid != -1)
	{
		g_glovar.g_exit_status = 131;
		write(1, "Quit: 3\n", 8);
	}
}

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			write(1, "\nGAEPOSHELL$ ", 13);
			g_glovar.g_exit_status = 1;
		}
		else
		{
			write(1, "\n", 1);
			g_glovar.g_exit_status = 130;
		}
	}
	else if (signo == SIGQUIT)
		signal_exit(pid);
}
