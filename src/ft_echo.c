/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:29:03 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 16:55:13 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_n_opt(int *n_option, t_parse_node *p, int i)
{
	int	j;

	j = 1;
	while (p->cmd[i][j] && p->cmd[i][j] == 'n')
		j++;
	if (p->cmd[i][j] != '\0')
		p->lex[i] = ARG;
	else
		*n_option = 1;
}

int	ft_echo(t_parse_node *p, t_info *info)
{
	int		i;
	int		n_option;

	(void)info;
	i = 0;
	n_option = 0;
	while (p->cmd[i])
	{
		if (p->lex[i] == OPT)
			check_n_opt(&n_option, p, i);
		if (p->lex[i] == ARG)
		{
			ft_putstr_fd(p->cmd[i], 1);
			if (p->cmd[i + 1] && p->cmd[i][0] != '\0')
				write(1, " ", 1);
		}
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
