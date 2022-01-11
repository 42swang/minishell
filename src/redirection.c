/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:09:47 by swang             #+#    #+#             */
/*   Updated: 2022/01/11 18:29:51 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// > < >> <<
/*
# define IN_RE 200
# define IN_FILE 201

# define HEREDOC 300
# define HERE_FILE 301

# define OUT_RE 400
# define OUT_FI 401

# define OUT_RE2 500
# define OUT_FI2 501
*/

void	pre_open(t_info *info)
{
	int	i;
	t_lex_node *ptr;

	i = 0;
	ptr = info->lex_list->head;
	//ft_print_lex_list(info);
	while (ptr)
	{
		if (ptr->type == IN_FILE || ptr->type == OUT_FI || ptr->type == HERE_FILE || ptr->type == OUT_FI2)
			i++;
		ptr = ptr->next;
	}
	info->file = (int *)ft_calloc(i + 1, sizeof(int));	
	i = 0;
	ptr = info->lex_list->head;
	while (ptr)
	{
		if (ptr->type == IN_FILE)
			info->file[i] = open(ptr->value, O_RDONLY);
		else if (ptr->type == OUT_FI)
			info->file[i] = open(ptr->value, O_RDWR | O_CREAT | O_TRUNC, 00644);
//		else if (ptr->type == HERE_FILE)
		else if (ptr->type == OUT_FI2)
			info->file[i] = open(ptr->value, O_RDWR | O_CREAT | O_APPEND, 00644);
		else
			i--;
		i++;
		ptr = ptr->next;
	}
}

void	make_cmd_lex(t_parse_node **p)
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
}
/*
int	is_heredoc(t_parse_node *p)
{
	while (p->cmd != HEREDOC)
	
}*/

void	here_document(t_parse_node *p)
{
	char	*end;
	char	*line;
	int		i;
	int		fd;

	//printf("here in\n");
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 00644);
	i = 0;
	while (p->lex[i] != HERE_FILE)
		i++;
	end = p->cmd[i];
	while(42)
	{
		line = readline("> ");
		if (ft_strncmp(end, line, ft_strlen(line) + 1) == 0)
			break ;
		ft_putendl_fd(line, fd);
		//히얼독과 에코가 만나면 빈개행만 출력
		free(line);
	}
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	if (ft_strncmp(p->cmd[i], "echo", 5) == 0)
		write(1, "\n", 1);
	else if (ft_strncmp(p->cmd[i], "cat", 4) == 0)
		make_cmd_lex(&p);
	printf("here\n");
	//ft_print_str_arr(p->cmd);
	//ft_print_fd(p->lex);
}

void	in_redirection(t_info *info, int idx)
{
	//< file grep
	//grep은 0에서 입력을 가져오는데 file에서 가져오도록 해야함
	dup2(info->file[idx], 0);
	close(info->file[idx]);
	
	//info->file_idx++; 리다이렉션에 들어올때마다 info->file_idx값이 변화함
}

void	out_redirection(t_info *info, int idx)
{
	//cat > file : 입력상태유지, 개행으로 전달된 내용이 파일에 저장됨. ^D (^C?)
	//cat > 1 > 2 > 3 > 4 > 5
	//마지막으로 나오는 파일의 fd배열인덱스를 기억
//	printf("%d %d %d %d %d\n", info->file[0], info->file[1], info->file[2], info->file[3], info->file[4]);
//	printf("fd : %d, idx : %d\n", info->file[idx - 1], idx);
	dup2(info->file[idx], 1);
	close(info->file[idx]);
}

void	out2_redirection(t_info *info, int idx)
{
	//cat > file : 입력상태유지, 개행으로 전달된 내용이 파일에 저장됨. ^D (^C?)
	
	//bash-3.2$ cat >> apen >> newap
	/*
		cat >> apen 의 내용이 newap로 복사되지않음
		cat >> apen >> newap 명령어 이후 쓰여진 내용은 newap에만 들어간다
	*/
	dup2(info->file[idx], 1);
	close(info->file[idx]);
}

void	redirection(t_info *info, t_parse_node *p)
{
	int	i;
	int	in;
	int out;
	int	out2;
	//int temp;

	i = 0;
	in = 0;
	out = 0;
	out2 = 0;
	//idx = info->file_idx;
	while (p->lex[i])
	{
		//ft_putendl_fd("redirection", 2);
		if (p->lex[i] == IN_RE)
		{
			ft_putnbr_fd(1, 2);
			in_redirection(info, in);
			in++;
		}
		else if (p->lex[i] == HEREDOC)
		{
			ft_putnbr_fd(2, 2);
			
			here_document(p);
		}
		else if (p->lex[i] == OUT_RE)
		{
			ft_putnbr_fd(3, 2);

			out_redirection(info, out);
			out++;
		}
		else if (p->lex[i] == OUT_RE2)
		{
			//printf("아웃투\n"); 
			ft_putnbr_fd(4, 2);
			
			out2_redirection(info, out2);
			out2++;
		}
		i++;
	}
	//printf("탈출\n");
}
