/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:08:02 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 18:02:41 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_path_str(t_env_node *ptr)
{
	char	*path_str;

	path_str = 0;
	while (ptr)
	{
		if (ft_strncmp(ptr->env_arr[0], "PATH", 5) == 0)
			break ;
		ptr = ptr->next;
	}
	if (ptr == NULL)
		return (NULL);
	path_str = ft_strdup(ptr->env_arr[1]);
	return (path_str);
}

static char	**get_path_arr(char	**temp_arr)
{
	int		i;
	char	*temp_str;

	i = 0;
	while (temp_arr[i])
	{
		temp_str = ft_strjoin(temp_arr[i], "/");
		if (temp_str == NULL)
			return (NULL);
		free(temp_arr[i]);
		temp_arr[i] = temp_str;
		i++;
	}
	return (temp_arr);
}

char	**get_path(t_env_list *list)
{
	char	*path_str;
	char	**temp_path_arr;

	path_str = get_path_str(list->head);
	if (path_str == NULL)
		return (NULL);
	temp_path_arr = ft_split(path_str, ':');
	free(path_str);
	path_str = 0;
	if (temp_path_arr == NULL)
		return (NULL);
	return (get_path_arr(temp_path_arr));
}
