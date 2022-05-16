/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:09:47 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:56:42 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	no_env_path(void)
{
	ft_putendl_fd("bash: cd: No such file or directory", 2);
	return (1);
}

void	set_pwd(t_env_node *env)
{
	char	*buf;

	while (env && env->next)
	{
		if (ft_strncmp(env->env_arr[0], "PWD", 3) == 0)
		{
			free(env->env_arr[1]);
			env->env_arr[1] = 0;
			buf = getcwd(NULL, 0);
			env->env_arr[1] = ft_strdup(buf);
		}
		env = env->next;
	}
	free(buf);
	buf = 0;
}
