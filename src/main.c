/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2021/12/10 15:40:37 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	char			*line;
	t_info			info;

	//sig_init();
	//print_ascii_art();
	(void)argc;
	(void)argv; //unused 어쩌고 에러땜에 추가
	init_info(&info);
	info.env_list = make_env_list(envp);
	while(42)
	{
		line = readline("GAEPOSHELL$ ");
		if (line || *line)
			add_history(line);
		else if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		ft_print_env_list(info.env_list);
		//parsing(line, &info);
		//pre_open();
		//ft_execute(&info);
	  	//delete_line(&info, line);
		//렉서랑 파서 리스트 초기화
	}
	//인포에있는거 초기화...
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}

