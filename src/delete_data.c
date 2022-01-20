/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:00:42 by swang             #+#    #+#             */
/*   Updated: 2022/01/20 13:33:29 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_parse(t_parse_list *list)
{
	t_parse_node *p;

	p = list->head;
	list->curr = p;
	while (p)
	{
		list->curr = p->next;
		free(p->cmd);
		printf("p->cmd\n");
		free(p->lex);
		printf("p->lex\n");
		free(p);
		printf("p\n");
		p = list->curr;
	}
}

void	free_lex(t_lex_list *list)
{
	t_lex_node *p;

	p = list->head;
	list->curr = p;
	while (p)
	{
		list->curr = p->next;
		free(p);
		p = list->curr;
	}
}

void	free_list(t_info *info)
{
	if (info->lex_list != 0)
	{
		printf("lex\n");
		free_lex(info->lex_list);
		free(info->lex_list);
		info->lex_list = 0;
	}
	if (info->parse_list != 0)
	{
		printf("parse\n");
		free_parse(info->parse_list);
		free(info->parse_list);
		info->parse_list = 0;
	}
}

void	delete_line(t_info *info, char *line)
{
	free(line);
	line = 0;
	//dup2(info->stdin_fd, STDIN);
	//dup2(info->stdout_fd, STDOUT);
	if (info->real)
	{
		printf("real\n");
		free(info->real);
		info->real = 0;
	}
	if (info->file)
	{
		printf("file\n");
		free(info->file);
		info->file = 0;
	}
	if (info->path)
	{
		printf("path\n");
		free_2d(info->path);
		info->path = 0;
	}
	if (info->token)
	{
		printf("token\n");
		free_2d(info->token);
		info->token = 0;
	}
	if (info->cmd_arr != 0)
	{
		printf("cmd_arr\n");
		free_2d(info->cmd_arr);
		info->cmd_arr = 0;
	}
	free_list(info);
	info->quote = 0;
}

	/*
		line과 관련된 애들 정보 지우기 (새 라인을 받아올거니까)
		2. 토큰 배열 초기화
		3. info 구조체중에 초기화 해야할거 초기화 해주기
			info.real 동적할당된 int배열 free
			info->token = 0; // 2차원 배열 free
			info->quote = 0; // 전부 off 시켜주자

		info->exit_stat는 종료값을 넣어줘야함
		*/
