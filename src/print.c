/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:29:12 by swang             #+#    #+#             */
/*   Updated: 2021/12/24 03:50:55 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_env_list(t_env_list *ptr)
{
	t_env_node *p = ptr->head;
	while (p)
	{
		printf("[%s] : [%s]\n", p->env_arr[0], p->env_arr[1]);
		p = p->next;
	}
}

/*
void	ft_print_lex_list(t_info *info)
{
	t_lexical_node *ptr = info->lex_list->head;
	while (ptr)
	{
		printf("		[%s][%d]\n", ptr->value, ptr->type);
		ptr = ptr->next;
	}
}

void	ft_print_parse_list(t_info *info)
{
	t_parse_node *ptr = info->parse_list->head;
	int x = 0;
	while (ptr)
	{
		printf("	------------\n");
		while (ptr->cmd[x])
		{
			printf("	[%s]:", ptr->cmd[x]);
			if (ptr->lex[x] == 555)
				printf("[CMD]\n");
			else if (ptr->lex[x] == 556)
				printf("[OPT]\n");
			else if (ptr->lex[x] == 557)
				printf("[ARG]\n");
			else if (ptr->lex[x] == 100)
				printf("[PIPE}\n");
			else if (ptr->lex[x] % 100 == 1)
				printf("[FILE]\n");
			else
				printf("{REDIR]\n");
			x++;
		}
		printf("	------------\n");
		x = 0;
		ptr = ptr->next;
	}
}
*/

void	ft_print_str_arr(char **arr)
{
	int x = 0;
	printf("			start print_str_arr\n");
	while (arr[x])
	{
		printf("			[%s]\n", arr[x]);
		x++;
	}
	printf("			end print_str_arr\n");
}
