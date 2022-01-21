/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:44:24 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 15:53:30 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_heredoc_p(t_parse_node *p, t_info *info)
{
	int	i;
	struct stat buf;

	i = 0;
	while (p->lex[i] && p->lex[i] != HEREDOC)
		i++;
	if (p->lex[i] == HEREDOC)
	{
		if ((stat("heredoc_tmp_42", &buf)) == 0) //stat함수 실패시 -1반환함
		{
			unlink("heredoc_tmp_42");
			info->heredoc = 0;
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

void	here_document(t_parse_node *p, int idx)
{
	char	*end;
	char	*line;
	int		i;
	int		fd;

	//printf("here in\n");
	fd = open("heredoc_tmp_42", O_RDWR | O_CREAT | O_TRUNC, 00700);
	i = idx;
	while (p->lex[i] != HERE_DEL)
		i++;
	end = p->cmd[i];
	while(42)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_putstr_fd("\x1b[1A", 1);
			ft_putstr_fd("\033[2C", 1);
			ft_putstr_fd("", 1);
			break ;
		}
		if (ft_strncmp(end, line, ft_strlen(line) + 1) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
}
