/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2022/01/11 18:36:54 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit_status;

int	main(int argc, char *argv[], char **envp)
{
	char			*line;
	t_info			info;
	
	g_exit_status = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	//sig_init();
	//print_ascii_art();
	(void)argc;
	(void)argv; //unused 어쩌고 에러땜에 추가
	init_info(&info);
	info.path = get_path(envp);
	info.env_list = make_env_list(envp);
	while(42 && *(info.run_exit) != 1)
	{
		
		line = readline("GAEPOSHELL$ ");
		if (line)//*line
			add_history(line);
		else if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (sin_error(line))
			printf("bash: syntax error\n");
		else if (parsing(line, &info) == -1)
			printf("bash: syntax error\n");
		else
			ft_execute(&info);
		printf("info %d,%d\n", *(info.run_exit), info.exit_stat);
		if (*(info.run_exit) == 1)
		{
			printf("test1 %d %d\n", info.exit_stat, *(info.run_exit));
			exit(255);
		}
		printf("test2 %d %d\n", info.exit_stat, *(info.run_exit));
	//*
	//*
	//자식프로세스가 info->내용물을 수정했을 떄 반영되지않음.
	//*
	//*
	//delete_line(&info, line);
		//parsing(line, &info);
	}
	//인포에있는거 초기화...
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}

