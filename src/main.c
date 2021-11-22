/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2021/11/21 02:26:25 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_info			info;
	t_parse_list	*parse_list;

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
		}
		parse_list = run_parsing(line, &info); //입력받은 라인과 info구조체넘겨서 파싱하
		if (info.token != NULL) //token 한글자씩 찍는 테스트문
		{
			int x = 0;
			while (info.token[x])
			{
				printf("%s\n", info.token[x]);
				/*
				int y = 0;
				while (info.token[x][y])
				{
					printf("%c", info.token[x][y]);
					y++;
				}
				printf(" ");
				*/
				x++;
			}
		}
		// 실행파트
		// line과 관련된 애들 정보 지우기 (새 라인을 받아올거니까)
		free(line);
	}
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}



/*
if (ft_strncmp(line, "path", 4) == 0)
{
	int k = 0;
	while (info.path[k])
	{
		printf("%s\n", info.path[k]);
		k++;
	}
}
//환경변수에서 path분리하는 부분 테스트용 if문
*/