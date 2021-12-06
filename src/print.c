/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:29:12 by swang             #+#    #+#             */
/*   Updated: 2021/12/06 14:29:58 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_parse_list(t_info *info)
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
			else
				printf("[R,P]\n");
			x++;
		}
		printf("	------------\n");
		x = 0;
		ptr = ptr->next;
	}
}