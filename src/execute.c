/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:36:19 by swang             #+#    #+#             */
/*   Updated: 2021/12/09 15:41:58 by swang            ###   ########.fr       */
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

void	run_no_pipe(t_parse_node *p, t_info *info)
{
	//cmd = {cat}{-e}{>}{file}
	//lex = {CMD}{OPT}{RE}{ARG}

	int i;
	char *cmd_path;
	char **cmd_arr;
	i = 0;
	
	redirection(info, p);
	while (p->lex[i] != CMD)
		i++;
	//print_str_arr(info->path);
	cmd_path = find_cmd_path(info->path, p->cmd[i]);
	//printf("		access path : %s\n", cmd_path);
	cmd_arr = make_cmd_arr(p, info);
	//ft_print_str_arr(cmd_arr);
	if(execve(cmd_path, cmd_arr, info->envp) == -1)
		printf("command not found\n");
	info->exit_stat = 42;
	exit(0); //자식프로세스 종료
	//비정상 프로세스 종료값 추가하기
}

void	pipe_head_node(t_info *info, t_parse_node *p)
{
	int	i;
	// 안쓰는 파이프는 닫고, 출력을 파이프로 보내는 작업
	dup2(p->p_fd[1], 1);
	close(p->p_fd[1]);
	close(p->p_fd[0]);
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) == 1)
	{
		write(2, "builtin\n", 9);
		//run_builtin(p, info);
	}
	else
		run_no_pipe(p, info);
	exit(0);
}

void	pipe_middle_node(t_info *info, t_parse_node *p)
{
	int	i;
	// 입력 출력을 파이프로
	dup2(p->prev->p_fd[0], 0);
	dup2(p->p_fd[1], 1);
	close(p->p_fd[0]);
	close(p->p_fd[1]);
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) == 1)
	{
		write(2, "builtin\n", 9);
		//run_builtin(p, info);
	}
	else
		run_no_pipe(p, info);
}

void	pipe_tail_node(t_info *info, t_parse_node *p)
{
	int	i;
	// 안쓰는 파이프는 닫고, 입력을 파이프에서 받아오는 작업
	dup2(p->prev->p_fd[0], 0);
	close(p->p_fd[0]);
	close(p->p_fd[1]);
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) == 1)
	{
		printf("빌트인 함수\n");
		//run_builtin(p, info);
	}
	else
		run_no_pipe(p, info);
	exit(0);
}


void	run_pipe(t_info *info, t_parse_node *p)
{
	int i;
	int j;
	int *pid;
	t_parse_node *tmp;

	i = 0;
	tmp = info->parse_list->head; 
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	pid = (int *)ft_calloc(i + 1, sizeof(int));
	j = 0;
	while (j < i)
	{
		pipe(p->p_fd);
		pid[j] = fork();
		//printf("pid[%d]\n", pid[j]);
		if (pid[j] == 0)
			break ;
		wait(0);
		close(p->p_fd[1]);
		p = p->next;
	}
	if (j < i && pid[j] == 0)
	{
		//printf("%d, %d\n", j, pid[j]);
		//printf("pid[%d], [%d]\n", getpid(), getppid());
		//printf("in[%d], out[%d]\n", p->p_fd[0], p->p_fd[1]);
		if (info->parse_list->head == p)
		{
			//printf("머리\n");
			pipe_head_node(info, p);
		}
		else if(p != info->parse_list->tail) //파이프 중간
		{
			//printf("중간\n");
			pipe_middle_node(info, p);
		}
		else //파이프 마지막
		{
			//printf("끝\n");
			pipe_tail_node(info, p);
		}
		exit(0); //임시종료
	}
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
			run_pipe(info, p);
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
