#include "../include/minishell.h"

int			env_add(const char *value, t_env_node *env)
{
	t_env_node	*new;
	t_env_node	*tmp;

	if (env && env->env_arr[0] == NULL)
	{
		env->env_arr[1] = ft_strdup(value);
		return (0);
	}
	if (!(new = malloc(sizeof(t_env_node))))
		return (-1);
	new->env_arr[1] = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

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

static char		*get_env_path(t_env_node *env, const char *var)
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

static int		update_oldpwd(t_env_node *env)
{
	char	cwd[999];

	if (getcwd(cwd, 999) == NULL)
		return (1);
	if (is_in_env(env, cwd) == 0)
		env_add(cwd, env);
	return (0);
}

static int		go_to_path(int option, t_env_node *env, t_parse_node *p)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME");
		if (!env_path)
		{
			printf("bash: cd: %s: No such file or directory\n", p->cmd[1]);
			return (1);
		}
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD");
		if (!env_path)
		{
			printf("bash: cd: %s: No such file or directory\n", p->cmd[1]);
			return (1);
		}
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	free(env_path);
	return (ret);
}

int				ft_cd(t_parse_node *p, t_info *info)
{
	int		cd_ret;

	if (!p->cmd[1])
		return (go_to_path(0, info->env_list->head, p));
	if (p->cmd[1][0] == '-')
		cd_ret = go_to_path(1, info->env_list->head, p);
	else
	{
		update_oldpwd(info->env_list->head);
		cd_ret = chdir(p->cmd[1]);
	}
	return (cd_ret);
}