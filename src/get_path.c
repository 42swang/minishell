/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 22:08:02 by swang             #+#    #+#             */
/*   Updated: 2021/11/20 22:58:12 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_path_str(char *envp[])
{
	int		i;
	char	*path_str;

	i = 0;
	path_str = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
			//환경변수에서 PATH=를 찾았다는 뜻
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	path_str = ft_strdup(envp[i] + 5);
	return (path_str);
}

static char	**get_path_arr(char	**temp_arr)
{
	int	i;
	char	*temp_str;

	i = 0;
	while(temp_arr[i])
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

char	**get_path(char	*envp[])
{
	char	*path_str;
	char	**temp_path_arr;

	path_str = get_path_str(envp);
	if (path_str == NULL)
		return (NULL);
	temp_path_arr = ft_split(path_str, ':');
	free(path_str);
	if (temp_path_arr == NULL)
		return (NULL);
	return (get_path_arr(temp_path_arr));
}