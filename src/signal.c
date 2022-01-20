#include "../include/minishell.h"

void handle_signal(int signo)
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
			glovar.g_exit_status = 1;
		}
		else
		{
			write(1, "\n", 1);
			glovar.g_exit_status = 130;
		}
	}
	else if (signo == SIGQUIT)
	{
		if (pid != -1)
		{
			glovar.g_exit_status = 131;
			write(1, "Quit: 3\n", 8);
		}
	}
}

/*
void sig_init()
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}*/
// main에 sig_init(); 추가
// 헤더파일에 # include <signal.h> 추가
