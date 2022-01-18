/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:36:19 by swang             #+#    #+#             */
/*   Updated: 2022/01/18 15:14:52 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void run_builtin(t_parse_node *p, t_info *info)
{
	char *cmd;
	int	ret;
	int i;

	ret = 0;
	i = 0;
	ft_isheredoc(info);
	redirection(info, p);
	while (p->lex[i] != CMD)
		i++;
	cmd = p->cmd[i];
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ret = ft_echo(p, info);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ret = ft_cd(p, info);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ret = ft_pwd(p, info);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ret = ft_exit(p, info);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ret = ft_env(info);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ret = ft_unset(info, p, i);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ret = ft_export(info, p, i);
	g_exit_status = ret;
}

void	run_no_pipe(t_parse_node *p, t_info *info)
{
	//cmd = {cat}{-e}{>}{file}
	//lex = {CMD}{OPT}{RE}{ARG}

	int i;
	char *cmd_path;
	char **cmd_arr;
	i = 0;
	
	ft_putendl_fd("in run no pipe", 2);
	redirection(info, p);
	while (p->lex[i] && p->lex[i] != CMD)
		i++;
	if (p->lex[i] == 0 && p->lex[0] == HEREDOC)
		exit(0); //히얼독일때 cmd없음, 종료값 어떻게 할거? -> bash 따라 0S
	cmd_path = find_cmd_path(info->path, p->cmd[i]);
//	printf("		access path : %s\n", cmd_path);
	cmd_arr = make_cmd_arr(p, info);
	ft_print_str_arr(cmd_arr);
	execve(cmd_path, cmd_arr, info->envp);
	printf("command not found\n");
	exit(127); //자식프로세스 종료
}

void	pipe_head_node(t_info *info, t_parse_node *p)
{
	int	i;
	// 안쓰는 파이프는 닫고, 출력을 파이프로 보내는 작업
	// 리다이렉션이 파이프처리 어디쯤에 들어가야하는거지
	dup2(p->p_fd[1], 1);
	close(p->p_fd[1]);
	close(p->p_fd[0]);
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_isbuiltin(p->cmd[i]) == 1)
	{
		run_builtin(p, info);
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
		run_builtin(p, info);
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
		//printf("빌트인 함수\n");
		run_builtin(p, info);
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

int run_execute(t_info *info)
{
	t_parse_node *p;
	int	i;

	p = info->parse_list->head;
	i = 0;
	printf("test3\n");
	ft_isheredoc(info);
	printf("test4\n");
	while (p->lex[i] && p->lex[i] != CMD)
	{
		i++;
		printf("%d\n", i);
	}
	printf("p->lex[%d] = %s", i, p->cmd[i]);
	// p->lex[i]가 존재할 때 조건을 빼먹어서 p->lex[i]의 값이 이상한 곳을 참조하고있었음
	// CMD가 없을 때 임시로 i값을 0으로 두었더니 히얼독의 경우 실행파트에서 command not found가 뜬다.
	if (p->lex[i] == 0)
		i = 0;
	if (ft_isbuiltin(p->cmd[i]) && !(p->next))
	{
	//	ft_putendl_fd("go builtin", 2);
		run_builtin(p, info);
	}
	else
	{
		if (!(p->next))
		{
	//		ft_putendl_fd("go run_no_pipe", 2);
			run_no_pipe(p, info);
		}
		else
		{
		//	ft_putendl_fd("go run_pipe", 2);
			run_pipe(info, p);
		}	
	}
	return (info->exit_stat);
}

void ft_execute(t_info *info)
{
	int	pid;
	int	status;
	int	ret_child;

	pid = fork();
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		printf("test1\n");
		pre_open(info);
		printf("test2\n");
		ret_child = run_execute(info);
		exit (ret_child); // 여기서 무조건 종료시켜야함... 자식프로세스가 메인문까지 되돌아가고 있음...
	}
	else
	{
		wait(&status);
		printf("			return1(%d), return2(%d)\n", WIFEXITED(status), WEXITSTATUS(status));
		printf("			exit(%d)\n", status >> 8); //자식프로세스에서 exit()한 값
		//여기서 어떤 값이냐에 따라서 개포쉘을 종료시킬 수 있을까?
	}
}
