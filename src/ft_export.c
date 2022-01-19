/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:58:36 by swang             #+#    #+#             */
/*   Updated: 2022/01/19 14:34:06 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
static int	export_env(char *env, t_env_list *list, int sort)
{
	t_env_node *new;

	new = make_new_env(env);
	return (0);
}

*/
/*
static int	find_count(char *list, char *name)
{
	int	 ret;

	ret = 0;
	if (*list > *name)
	{
		return (1);
	}
	else if (*list && *name && *list == *name) //아예 똑같은게 있으면 교체되어야함 미리 예외처리하기
	{
		ret += find_count(list + 1, name + 1);
	}
	else
	{
		return (-1);
	}
	return (0);
}
*/

static int find_idx(char *old, char *new)
{
	char	c_old;
	char	c_new;

	c_old = *old;
	c_new = ft_toupper(*new);
	if (c_old > c_new) // new를 old 앞에다가
		return (1);
	else if (c_old == c_new) // new를 old 앞에다가
		return (0);
	else
		return (-1); // new > old old를 다음으로 넘기자
}

static int	find_sort(t_env_list *list, char *name)
{
	t_env_node *p;
	int			count;
	int			idx;

	p = list->head;
	idx = 0;
	count = 0;
	while (p)
	{
	//	printf("		in find_sort,		env_list :[%s], new_env : [%s]\n", p->env_arr[0], name);
		if (find_idx(p->env_arr[0], name) == -1) //old < new 일 때는 다음노드의 이름을 비교한다
		{
			p = p->next;
			count++;
		}
		else
			break;
	}
	return (count);
}

static void make_new_list(t_env_list **list, int sort, t_env_node **node)
{
	(*list)->curr = (*list)->head;
//	printf("	in make_new_list, sort: %d name: %s\n", sort, (*node)->env_arr[0]);
	if (sort == 0)
	{
		(*node)->next = (*list)->head;
		(*list)->head->prev = (*node);
		(*list)->head = *node;
		//printf("		head : %s\n", (*list)->head->env_arr[0]);
	}
	else
	{
		while (sort--)
			(*list)->curr = (*list)->curr->next;
		(*list)->curr->prev->next = (*node);
		(*node)->prev = (*list)->curr->prev;

		(*list)->curr->prev = (*node);
		(*node)->next = (*list)->curr;
	}
}

t_env_node	*make_env_node2(char **tmp)
{
	t_env_node	*new;

	new = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	if (new == 0)
	{
		ft_putendl_fd("Failed to make env node", 2);
		exit(0); // 말록실패
	}
	new->env_arr = (char **)ft_calloc(3, sizeof(char *));
	new->env_arr[0] = tmp[0];
	new->env_arr[1] = tmp[1];
	if (new->env_arr == 0)
	{
		ft_putendl_fd("Failed to make env_arr", 2);
		exit(0); // 말록실패
	}
	return (new);
}

static void	make_new(t_info *info, char **tmp)
{
	t_env_node	*new_node;
	int			sort;

	new_node = make_env_node2(tmp);
	sort = find_sort(info->env_list, new_node->env_arr[0]);
//	printf("	sort = %d\n", sort);
	make_new_list(&(info->env_list), sort, &new_node);
//	printf("				%s\n", info->env_list->head->env_arr[0]);
}

int	check_same(char *env, t_env_list *list)
{
	t_env_node *p;

	p = list->head;
	while (p)
	{
		if (ft_strncmp(env, p->env_arr[0], ft_strlen(env) + 1) == 0)
		{
			list->curr = p;
			return (1);
		}
		p = p->next;
	}
	return (0);
}

void	modi_env_list(t_info *info, char **tmp)
{
	t_env_node *p;
	char *value;

	p = info->env_list->curr;
	value = tmp[1];
	free(p->env_arr[1]);
	p->env_arr[1] = ft_strdup(value);
}

int	ft_export_exception(char **tmp)
{
	char	*name;
	int	i;

	i = 1;

	name = tmp[0];
	if (ft_isalpha(name[0]) == 0)
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		return (-1);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0)
		{
			ft_putendl_fd("export: not a valid identifier", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	print_declare(t_env_list *list)
{
	t_env_node *p;

	p = list->head;
	while (p)
	{
		printf("declare -x ");
		printf("%s", p->env_arr[0]);
		printf("=");
		printf("\"%s\"\n", p->env_arr[1]);
		p = p->next;
	}
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	ft_export(t_info *info, t_parse_node *p, int i)
{
	int	idx;
	char *env;
	char **tmp;

	env = p->cmd[i + 1];
	if (check_equal(env) == 0)
	{
		print_declare(info->env_list);
		info->exit_stat = 0;
		return (0);
	}
	idx = check_equal(env);
	tmp = (char **)ft_calloc(3, sizeof(char *));
	tmp[0] = ft_substr(env, 0, idx);
	tmp[1] = ft_substr(env + idx + 1, 0, ft_strlen(env + idx + 1));
	printf("%s, %s\n", tmp[0], tmp[1]);
	if (ft_export_exception(tmp) == -1)
	{
		printf("exception\n");
		return (-1);
	}
	if (check_same(tmp[0], info->env_list))
	{
		printf("same\n");
		modi_env_list(info, tmp);
	}
	else
	{
		printf("make new\n");
		make_new(info, tmp);
	}
	return (1); // 반환값...
}
