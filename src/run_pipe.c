/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:19:12 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 16:45:01 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_parse_list(t_parse_node *p)
{
	int	count;

	count = 0;
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}

void	sort_pipe(t_info *info, t_parse_node *p)
{
	if (info->parse_list->head == p)
		pipe_head_node(info, p);
	else if (p != info->parse_list->tail)
		pipe_middle_node(info, p);
	else
		pipe_tail_node(info, p);
	exit(0);
}

void	run_no_pipe(t_parse_node *p, t_info *info)
{
	int		i;
	char	*cmd_path;
	char	**cmd_arr;

	i = 0;
	redirection(info, p);
	while (p->lex[i] && p->lex[i] != CMD)
		i++;
	if (p->lex[i] == 0 && p->lex[0] == HEREDOC)
		exit(0);
	info->path = get_path(info->env_list);
	cmd_path = find_cmd_path(info->path, p->cmd[i]);
	cmd_arr = make_cmd_arr(p, info);
	back_term();
	execve(cmd_path, cmd_arr, info->envp);
	ft_putendl_fd("command not found", 2);
	exit(127);
}

void	run_pipe(t_info *info, t_parse_node *p)
{
	int				i;
	int				j;
	int				*pid;

	j = 0;
	i = count_parse_list(p);
	pid = (int *)ft_calloc(i + 1, sizeof(int));
	while (j < i)
	{
		pipe(p->p_fd);
		pid[j] = fork();
		if (pid[j] == 0)
			break ;
		wait(0);
		close(p->p_fd[1]);
		p = p->next;
	}
	if (j < i && pid[j] == 0)
		sort_pipe(info, p);
}
