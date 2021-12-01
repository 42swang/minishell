/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2021/11/30 17:36:39 by swang            ###   ########.fr       */
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
	/*
		printf("in main : print lexer_list\n");
		t_lexical_node *pp;
		pp = info.lex_list->head;
		while (pp)
		{
			printf("	{TOK : %s} {TYPE : %d}\n", pp->value, pp->type);
			pp = pp->next;
		}
		*/

		printf("in main : print parse_list\n");
		t_parse_node *p;
		p = info.parse_list->head;
		int xx = 0;
		while (p)
		{
			printf("	parse[%d]\n",p->index);
			printf("{ ");
			while (p->cmd[xx])
			{
				printf("[%s]", p->cmd[xx]);
				xx++;
			}
			printf(" }\n");
			xx = 0;
			printf("{ ");
			while (p->lex[xx])
			{
				printf("[%d]", p->lex[xx]);
				xx++;
			}
			xx = 0;
			printf(" } end\n");
			p = p->next;
		}


/*
*/

		//실행
	//	delete_line(&info, line);
		//렉서랑 파서 리스트 초기화
	}
	//인포에있는거 초기화...
	//프로그램 종료 전 실행해야하는 것들
	return (0);
}
/*
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
