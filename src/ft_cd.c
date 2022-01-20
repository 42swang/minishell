#include "../include/minishell.h"
/*
int			env_add(const char *value, t_env_node *env)
{
	t_env_node	*new;
	t_env_node	*tmp;

	printf("check		9\n");
	if (env && env->env_arr[0] == NULL)
	{
		env->env_arr[1] = ft_strdup(value);
		return (0);
	}
	printf("check		10\n");
	if (!(new = malloc(sizeof(t_env_node))))
		return (-1);
	printf("check		11\n");
	new->env_arr[1] = ft_strdup(value);
	printf("check		12\n");
	while (env && env->next && env->next->next)
		env = env->next;
	printf("check		13\n");
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	printf("check		14\n");
	return (0);
}*/

int			is_in_env(t_env_node *env, char *args)
{
	while (env && env->next)
	{
		if (ft_strncmp(env->env_arr[0], "OLDPWD", 6) == 0)
		{
			//printf("args = %s, env->env_arr[0] = %s, env->env_arr[1] = %s\n", args, env->env_arr[0], env->env_arr[1]);
			free(env->env_arr[1]);
			env->env_arr[1] = ft_strdup(args);
			//printf("args = %s, env->env_arr[0] = %s, env->env_arr[1] = %s\n", args, env->env_arr[0], env->env_arr[1]);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char		*get_env_path(t_env_node *env, const char *var)
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
			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
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

static int		update_oldpwd(t_env_node *env, t_info *info)
{
	char	cwd[999];

	if (getcwd(cwd, 999) == NULL)
		return (1);
	is_in_env(env, cwd);
	/*
	if (is_in_env(env, cwd) == 0)
	{
		printf("check		7\n");
		env_add(cwd, env);
		printf("check		8\n");
	}*/
	info->old_pwd = ft_strdup(cwd);
	return (0);
}

static int		go_to_path(int option, t_env_node *env, t_parse_node *p, t_info *info)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env, info);
		env_path = info->home;
		if (!env_path)
		{
			printf("bash: cd: %s: No such file or directory\n", p->cmd[1]);
			return (1);
		}
	}
	else if (option == 1)
	{
		env_path = info->old_pwd;
		if (!env_path)
		{
			printf("bash: cd: %s: No such file or directory\n", p->cmd[1]);
			return (1);
		}
		update_oldpwd(env, info);
	}
	ret = chdir(env_path);
	free(env_path);
	return (ret);
}

int				ft_cd(t_parse_node *p, t_info *info)
{
	int		cd_ret;

	if (!p->cmd[1])
		return (go_to_path(0, info->env_list->head, p, info));
	if (p->cmd[1][0] == '-')
		cd_ret = go_to_path(1, info->env_list->head, p, info);
	else
	{
		update_oldpwd(info->env_list->head, info);
		cd_ret = chdir(p->cmd[1]);
	}
	return (cd_ret);
}
