/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:48 by swang             #+#    #+#             */
/*   Updated: 2022/01/20 20:57:58 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. 히얼독  파일이름 겹치지 않도록 수정
2. 종료상태값 수정
3. 함수 쪼개기
4.
*/


#include "../include/minishell.h"

int	check_no_pipe_builtin(t_info *info)
{
	int	i;
	int	*ptr;

	i = 0;
	ptr = info->parse_list->head->lex;
	while (ptr[i] && ptr[i] != CMD)
		i++;
	if (ptr[i] == 0)
		return (0);
	if (info->parse_list->head == info->parse_list->tail && ft_isbuiltin(info->parse_list->head->cmd[i]))
		return (1);
	else
		return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	char			*line;
	t_info			info;

	glovar.g_exit_status = 0;
	tcgetattr(0, &(glovar.old_term));
	tcgetattr(0, &(glovar.new_term));
	glovar.new_term.c_lflag &= ECHO;		// 입력 시 터미널에서 보이지 않기
	glovar.new_term.c_cc[VMIN] = 1;			// 최소 입력 버퍼 크기
	glovar.new_term.c_cc[VTIME] = 0;		// 버퍼비우는시간
	tcsetattr(0, TCSANOW, &(glovar.new_term));
	sig_init();
	use_arg(argc, argv);
	init_info(&info, envp);
	while(42)
	{
		line = readline("GAEPOSHELL$ ");
		if (line && *line != '\0')
			add_history(line);
		if (line == NULL)
		{
			ft_putstr_fd("\x1b[1A", 1);
			ft_putstr_fd("\033[12C", 1);
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		else if (*line == '\0')
		{
			free(line);
			continue;
		}
		if (sin_error(line))
			printf("syntax error near unexpected token\n");
		else if (parsing(line, &info) == -1)
			printf("syntax error near unexpected token\n");
		else
		{
			if (check_no_pipe_builtin(&info) == 1)
			{
				pre_open(&info);
				ft_isheredoc(&info);
				run_builtin(info.parse_list->head, &info);
			}
			else
				ft_execute(&info);
		}
		free_line(&info, line);
	}
	free_info(&info);
	while (1)
		system("leaks minishell");
	return (0);
}
