/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2022/01/19 17:10:41 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. 히얼독  파일이름 겹치지 않도록 수정
2. 종료상태값 수정
3. 함수 쪼개기
4.
*/


#include "../include/minishell.h"

int g_exit_status;


int	check_no_pipe_builtin(t_info *info)
{
	int	i;

	i = 0;
	while (info->parse_list->head->lex[i] != CMD)
		i++;
	if (info->parse_list->head == info->parse_list->tail && ft_isbuiltin(info->parse_list->head->cmd[i]))
		return (1);
	else
		return (0);
}

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
	info.env_list = make_env_list(envp); // PWD:
	while(42)
	{
		line = readline("GAEPOSHELL$ ");
		if (*line != '\0')
		{
			if (line)//*line
				add_history(line);
			else if (line == NULL)
			{
				printf("exit\n");
				exit(0);
			}
			if (sin_error(line))
				printf("syntax error near unexpected token\n");
			else if (parsing(line, &info) == -1)
				printf("syntax error near unexpected token\n");
			else
			{
				if (check_no_pipe_builtin(&info) == 1)
				{
					pre_open(&info);
					ft_isheredoc(&info);
					run_builtin(info.parse_list->head, &info);
				}
				else
					ft_execute(&info);
			}
		}
	//	printf("		exit_stat = [%d]\n", info.exit_stat);
			//delete_line(info, line);
	}
	//인포에있는거 초기화...
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}

