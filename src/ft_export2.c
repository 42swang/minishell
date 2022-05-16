/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:56:32 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 14:43:14 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_declare(t_env_list *list)
{
	t_env_node	*p;

	p = list->head;
	while (p)
	{
		printf("declare -x ");
		printf("%s", p->env_arr[0]);
		printf("=");
		printf("\"%s\"\n", p->env_arr[1]);
		p = p->next;
	}
	g_glovar.g_exit_status = 0;
	return (0);
}

int	ft_export_exception(char **tmp)
{
	char	*name;
	int		i;

	i = 1;
	name = tmp[0];
	if (name[0] != '_' && ft_isalpha(name[0]) == 0)
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		return (-1);
	}
	while (name[i])
	{
		if (name[i] != '_' && ft_isalnum(name[i]) == 0)
		{
			ft_putendl_fd("export: not a valid identifier", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}
