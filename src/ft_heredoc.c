/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:44:24 by swang             #+#    #+#             */
/*   Updated: 2022/01/11 22:34:57 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_isheredoc(t_parse_node *p)
{
	int	i;

	i = 0;
	while (p->lex[i])
	{
		if (p->lex[i] == HEREDOC)
			here_document(p, i);
		i++;
	}
}

/*
static void	make_cmd_lex(t_parse_node **p)
{
	int *tmp;
	char **temp;
	int	count;
	int i;

	count = 0;
	tmp = (*p)->lex;
	temp = (*p)->cmd;
	while ((*p)->lex[count])
		count++;
	(*p)->lex = (int *)ft_calloc(count + 2, sizeof(int));
	(*p)->cmd = (char **)ft_calloc(count + 2, sizeof(char *));
	i = 0;
	while (i < count)
	{
		(*p)->lex[i] = tmp[i];
		(*p)->cmd[i] = temp[i];
		i++;
	}
	(*p)->lex[i] = ARG;
	(*p)->cmd[i] = "heredoc";
	//printf("here_doc\n");
}*/

void	here_document(t_parse_node *p, int idx)
{
	char	*end;
	char	*line;
	int		i;
	int		fd;

	//printf("here in\n");
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 00700);
	i = idx;
	while (p->lex[i] != HERE_DEL)
		i++;
	end = p->cmd[i];
	printf("%s\n", end);
	while(42)
	{
		line = readline("> ");
		if (ft_strncmp(end, line, ft_strlen(line) + 1) == 0)
			break ;
		ft_putendl_fd(line, fd);
		//히얼독과 에코가 만나면 빈개행만 출력
		free(line);
	}
	/*
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_strncmp(p->cmd[i], "echo", 5) == 0)
		write(1, "\n", 1);
	else if (ft_strncmp(p->cmd[i], "cat", 4) == 0)
		make_cmd_lex(&p);
		*/
	//************66~69 까지 in redirection 작업(redirection.c)***********//


	//ft_print_str_arr(p->cmd);
	//ft_print_fd(p->lex);
}