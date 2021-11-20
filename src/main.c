/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2021/11/20 23:56:35 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_info			info;
	//t_parse_list	*parse_list;

	//추후 시그널처리 추가 예정
	//print_ascii_art();
	(void)argc;
	(void)argv; //unused 어쩌고 에러땜에 추가
	init_info(&info);
	info.path = get_path(envp);
	if (info.path == NULL)
		printf("Failed to find PATH in envp\n");
	while(42)
	{
		line = readline("GAEPOSHELL$ ");

		if (line || *line)
			add_history(line);
		else if (line == NULL)
		{
			printf("exit\n");
			exit(0);
			//line이 NULL인것과 *line이 NULL인것의 차이와 line이 NULL일 때 종료하는 이유
		}
		if (ft_strncmp(line, "path", 4) == 0)  //환경변수에서 path분리하는 부분 테스트용 if문
		{
			int k = 0;
			while (info.path[k])
			{
				printf("%s\n", info.path[k]);
				k++;
			}
		}
		free(line);
	}
}








/*
        parse_list = parse_line(line, envp_list);
        if (parse_list == 0){
           continue;
        }
        execute_line(parse_list, envp_list, shell_list);
        delete_parse_list(&parse_list);
*/