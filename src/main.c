/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2021/11/25 22:20:48 by swang            ###   ########.fr       */
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
	while(42)
	{
		make_env_list(&info);
		line = readline("GAEPOSHELL$ ");
		if (line || *line)
			add_history(line);
		else if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		
		//info.파서리스트 = run_parsing(line, &info);
		//파서구조체를 지워버려서 실행이 안됩니다~ 추가해주세용

		// 실행파트
		//환경변수 리스트초기화
		//렉서랑 파서 리스트 초기화
		//line과 관련된 애들 정보 지우기 (새 라인을 받아올거니까)
		free(line);
	}
	//인포에있는거 초기화...
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}
/*
		printf("-----in main : print token-----\n");
		if (info.token != NULL) //token 찍는 테스트문
		{
			int x = 0;
			while (info.token[x])
			{
				printf("	[%d:%s:(%d)]\n", x, info.token[x], info.real[x]);
				x++;
			}
			printf("-------------end main-------------\n");
		}
		*/
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
