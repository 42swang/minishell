/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:06:21 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:58:02 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_parse_node *p, t_info *info)
{
	char	*buf;

	(void)p;
	(void)info;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (-1);
	else
		printf("%s\n", buf);
	free(buf);
	buf = 0;
	return (0);
}
