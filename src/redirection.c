/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:09:47 by swang             #+#    #+#             */
/*   Updated: 2021/12/29 16:29:19 by swang            ###   ########.fr       */
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
	printf("in pre_open\n");
	//ft_print_lex_list(info);
	while (ptr)
	{
		printf("{%d}\n", info->lex_list->head->type);
		if (ptr->type == IN_FILE || ptr->type == OUT_FI || ptr->type == HERE_FILE || ptr->type == OUT_FI2)
			i++;
		ptr = ptr->next;
	}
	printf("%d\n", i);
	info->file = (int *)ft_calloc(i + 1, sizeof(int));	
	i = 0;
	ptr = info->lex_list->head;
	printf("in pre whilepre\n");
	while (ptr)
	{
		if (ptr->type == IN_FILE)
			info->file[i] = open(ptr->value, O_RDONLY);
		else if (ptr->type == OUT_FI)
			info->file[i] = open(ptr->value, O_RDWR | O_CREAT | O_TRUNC, 00644);
		else if (ptr->type == HERE_FILE)
			printf("히얼독\n");
		else if (ptr->type == OUT_FI2)
			info->file[i] = open(ptr->value, O_RDWR | O_CREAT | O_APPEND);
		else
			i--;
		i++;
		ptr = ptr->next;
	}
	printf("in pre whileafter\n");
}

void	in_redirection(t_info *info)
{
	//< file grep
	//grep은 0에서 입력을 가져오는데 file에서 가져오도록 해야함
	printf("in re\n");
	dup2(info->file[info->file_idx], 0);
	close(info->file[info->file_idx]);
	info->file_idx++;
}

void	redirection(t_info *info, t_parse_node *p)
{
	int	i;

	i = 0;
	while (p->lex[i])
	{
		if (p->lex[i] == IN_RE)
			in_redirection(info);
		else if (p->lex[i] == HEREDOC)
			printf("히얼독\n"); //heredoc(info, p, i);
		else if (p->lex[i] == OUT_RE)
			printf("아웃리\n"); //out_redirection(info, p, i);
		else if (p->lex[i] == OUT_RE2)
			printf("아웃투\n"); //out2_redirection(info, p, i);
		i++;
	}
}
