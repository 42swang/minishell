/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:36:19 by swang             #+#    #+#             */
/*   Updated: 2021/12/06 19:00:28 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
void run_builtin(t_parse_node *p, t_info *info)
{
	char *cmd;
	int	ret;
	int i;

	ret = 0;
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	cmd = p->cmd[i];
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ret = ft_echo(p, info);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ret = ft_cd(p, info);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ret = ft_pwd(p, info);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ret = ft_export(p, info);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ret = ft_unset(p, info);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ret = ft_env(p, info);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ret = ft_exit(p, info);
	info->exit_stat = ret;
}
*/

char **make_cmd_arr(t_parse_node *p, t_info *info)
{
	char **arr;
	int i = 0;
	int count = 0;
	while (p->lex[i] != CMD)
		i++;
	count++;
	i = 0;
	while (p->lex[i])
	{
		if (p->lex[i] == CMD || p->lex[i] == OPT || p->lex[i] == ARG)
			count++;
		i++;
	}
	arr = (char **)ft_calloc(count + 1, sizeof(char *));
	i = 0;
	int j = 1;
	while (p->lex[i])
	{
		if (p->lex[i] == CMD)
			arr[0] = ft_strdup(p->cmd[i]);
		else if (p->lex[i] == OPT || p->lex[i] == ARG)
			arr[j++] = ft_strdup(p->cmd[i]);
		i++;
	}
	info->cmd_arr = arr;
	return (arr);
}

void	run_no_pipe(t_parse_node *p, t_info *info)
{
	//cmd = {cat}{-e}{>}{file}
	//lex = {CMD}{OPT}{RE}{ARG}

	int i;
	char *cmd_path;
	char **cmd_arr;
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	//print_str_arr(info->path);
	cmd_path = find_cmd_path(info->path, p->cmd[i]);
	//printf("		access path : %s\n", cmd_path);
	cmd_arr = make_cmd_arr(p, info);
	print_str_arr(cmd_arr);
	if(execve(cmd_path, cmd_arr, info->envp) == -1)
		printf("command not found\n");
	info->exit_stat = 42;
	exit(0); //자식프로세스 종료
	//비정상 프로세스 종료값 추가하기
}

void run_execute(t_info *info)
{
	t_parse_node *p;
	int	i;

	p = info->parse_list->head;
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) && !(p->next))
	{
		printf("빌트인 함수 && 단일실행\n");
		//run_builtin(p, info);
	}
	else
	{
		if (!(p->next))
			run_no_pipe(p, info);
		else
		{	
			while (p != 0)
			{
				if(info->parse_list->head == p)
					printf("파이프 있고 헤드 노드일 때\n");
				else if(p != info->parse_list->tail) //파이프 중간
					printf("중간 노드일 떄\n");
				else //파이프 마지막
					printf("마지막 노드\n");
				p = p->next;
			}
		}
	}
}

void ft_execute(t_info *info)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit(0);
	else if (pid == 0)
		run_execute(info);
	else
		wait(NULL);
}
