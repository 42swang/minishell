#include "../include/minishell.h"

void handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		//자식 프로세스 있을때 추가해야함 근데 만들어진게 없어서 어떤형식을 넣어야할지 미지수라.. 나중에 추가
		printf("\n");
	}
	else if (signo == SIGQUIT)
	{
		//여기도 자식 프로세스
		printf("Quit: 3\n");
	}
}

void sig_init()
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
// main에 sig_init(); 추가
// 헤더파일에 # include <signal.h> 추가