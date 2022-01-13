/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:44:24 by swang             #+#    #+#             */
/*   Updated: 2022/01/13 16:02:40 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_heredoc_p(t_parse_node *p)
{
	int	i;
	struct stat buf;

	i = 0;
	while (p->lex[i] && p->lex[i] != HEREDOC)
		i++;
	if (p->lex[i] == HEREDOC)
	{
		if ((stat("heredoc", &buf)) == 0) //stat함수 실패시 -1반환함
		{
			ft_putendl_fd("in stat", 2);
			unlink("heredoc");
		}
	}
}


void	ft_isheredoc(t_info *info)
{
	int	i;
	t_parse_node *p;

	p = info->parse_list->head;
	while (p)
	{
		i = 0;
		while (p->lex[i])
		{
			if (p->lex[i] == HEREDOC)
				here_document(p, i);
			i++;
		}
		p = p->next;
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
	while(42)
	{
		line = readline("> ");
		if (ft_strncmp(end, line, ft_strlen(line) + 1) == 0)
			break ;
		ft_putendl_fd(line, fd);
		//히얼독과 에코가 만나면 빈개행만 출력-> 입력 리다이렉션과 같이 동작하기 때문에 에코에 파일을 인 리다이렉션하면 빈 개행만 출력된다.
		free(line);
	}
	/*
	*****************************************************
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_strncmp(p->cmd[i], "echo", 5) == 0)
		write(1, "\n", 1);
	else if (ft_strncmp(p->cmd[i], "cat", 4) == 0)
		make_cmd_lex(&p);
	*/
	//************ "<(in redirection) 작업과 같다(redirection.c)"***********//


	//ft_print_str_arr(p->cmd);
	//ft_print_fd(p->lex);
}