/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:35:54 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 20:35:55 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_cmd_path(char **arr, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	path = 0;
	if (arr == NULL)
		return (0);
	path = ft_strdup(cmd);
	if (access(path, X_OK | F_OK) == 0)
		return (path);
	else
		free(path);
	path = 0;
	while (arr[i])
	{
		path = ft_strjoin(arr[i], cmd);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		free(path);
		path = 0;
		i++;
	}
	return (NULL);
}
