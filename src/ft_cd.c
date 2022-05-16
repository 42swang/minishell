/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:09:47 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 17:57:12 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_in_env(t_env_node *env, char *args)
{
	while (env && env->next)
	{
		if (ft_strncmp(env->env_arr[0], "OLDPWD", 6) == 0)
		{
			free(env->env_arr[1]);
			env->env_arr[1] = 0;
			env->env_arr[1] = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_env_path(t_env_node *env, const char *var)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->env_arr[0], var, ft_strlen(var)) == 0)
		{
			s_alloc = ft_strlen(env->env_arr[1]);
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			if (!(oldpwd))
				return (NULL);
			i = 0;
			j = 0;
			while (env->env_arr[1][i])
				oldpwd[j++] = env->env_arr[1][i++];
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env_node *env, t_info *info)
{
	char	cwd[999];
	char	*tmp;

	tmp = 0;
	if (getcwd(cwd, 999) == NULL)
		return (1);
	is_in_env(env, cwd);
	tmp = info->old_pwd;
	info->old_pwd = ft_strdup(cwd);
	if (tmp)
		free(tmp);
	tmp = 0;
	return (0);
}

static int	go_to_path(int option, t_env_node *env, t_info *info)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env, info);
		env_path = info->home;
		if (!env_path)
			return (no_env_path());
	}
	else if (option == 1)
		return (-1);
	ret = chdir(env_path);
	free(env_path);
	env_path = 0;
	return (ret);
}

int	ft_cd(t_parse_node *p, t_info *info)
{
	int	cd_ret;

	if (!p->cmd[1])
		return (go_to_path(0, info->env_list->head, info));
	if (p->cmd[1][0] == '-')
		cd_ret = go_to_path(1, info->env_list->head, info);
	else
	{
		update_oldpwd(info->env_list->head, info);
		cd_ret = chdir(p->cmd[1]);
	}
	set_pwd(info->env_list->head);
	if (cd_ret == -1)
		ft_putendl_fd("bash: cd: No such file or directory", 2);
	return (cd_ret);
}
