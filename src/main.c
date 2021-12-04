/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2021/12/04 18:28:02 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_info			info;
  
	//sig_init();
	//print_ascii_art();
	(void)argc;
	(void)argv; //unused 어쩌고 에러땜에 추가
	init_info(&info, envp);
	make_env_list(&info);
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
		parsing(line, &info);
		ft_execute(&info);
		t_parse_node *p = info.parse_list->head;
		int x = 0;
		while (p)
		{
			printf("	------------\n");
			while (p->cmd[x])
			{
				printf("	[%s]:", p->cmd[x]);
				if (p->lex[x] == 555)
					printf("[CMD]\n");
				else if (p->lex[x] == 556)
					printf("[OPT]\n");
				else if (p->lex[x] == 557)
					printf("[ARG]\n");
				else
					printf("[R,P]\n");
				x++;
			}
			printf("	------------\n");
			x = 0;
			p = p->next;
		}
		//실행
	  //delete_line(&info, line);
		//렉서랑 파서 리스트 초기화
	}
	//인포에있는거 초기화...
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}

