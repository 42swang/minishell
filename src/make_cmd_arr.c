/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:00:13 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 21:10:55 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_cmd_arr(t_parse_node *p)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (p->lex[i] != CMD)
		i++;
	count++;
	i = 0;
	while (p->lex[i])
	{
		if (p->lex[i] == CMD || p->lex[i] == OPT || p->lex[i] == ARG)
			count++;
		i++;
	}
	return (count);
}

char	**make_cmd_arr(t_parse_node *p, t_info *info)
{
	char	**arr;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 1;
	count = count_cmd_arr(p);
	arr = (char **)ft_calloc(count + 1, sizeof(char *));
	while (p->lex[i])
	{
		if (p->lex[i] == CMD)
			arr[0] = ft_strdup(p->cmd[i]);
		else if (p->lex[i] == OPT || p->lex[i] == ARG)
			arr[j++] = ft_strdup(p->cmd[i]);
		i++;
	}
	info->cmd_arr = arr;
	return (arr);
}
