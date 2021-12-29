/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2021/12/24 20:01:52 by swang            ###   ########.fr       */
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
	while(42)
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
			printf("sin error1\n");
		else if (parsing(line, &info) == -1)
			printf("sin error2\n");
		else
			ft_execute(&info);
		//parsing(line, &info);
		//pre_open();
		//delete_line(info, line);
	}
	//인포에있는거 초기화...
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}

