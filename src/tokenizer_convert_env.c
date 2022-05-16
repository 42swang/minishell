/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_convert_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:31:17 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 18:03:01 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*change_shell_var(char *str, int *idx)
{
	int		len;
	char	*head;
	char	*tail;
	char	*ret;

	len = 0;
	ret = 0;
	if (ft_strncmp(str, "$?", 2) == 0)
	{
		head = ft_itoa(g_glovar.g_exit_status);
		len = ft_strlen(head);
		tail = ft_substr(str, 2, ft_strlen(str) - 2);
		ret = ft_strjoin(head, tail);
		free(head);
		head = 0;
		free(tail);
		tail = 0;
	}
	*idx += len;
	return (ret);
}

static char	*change_env_var(char *str2, int *idx, t_info *info)
{
	t_env_node	*p;
	int			len;
	char		*ret;

	p = info->env_list->head;
	*idx += 1;
	len = *idx;
	if (ft_isalpha(str2[*idx]) == 1 || str2[*idx] == '_')
	{
		while (ft_isalnum(str2[*idx]) == 1 || str2[*idx] == '_')
			*idx += 1;
		len = *idx - len;
		while (p)
		{
			if ((len == (int)ft_strlen(p->env_arr[0]))
				&& (ft_strncmp(str2 + 1, p->env_arr[0], len) == 0))
				return (change_env_var1(p->env_arr[1], str2, len));
			p = p->next;
		}
	}
	ret = ft_substr(str2 + 1, len, ft_strlen(str2 + len));
	*idx = 0;
	return (ret);
}

char	*convert_str2(char *str2, int *i, t_info *info)
{
	char	*convert;
	int		idx;

	idx = 0;
	convert = 0;
	if (str2[idx + 1] && (ft_isquote(str2[idx + 1])))
		convert = ft_substr(str2, 1, ft_strlen(str2));
	else if (str2[idx + 1] && str2[idx + 1] == '?')
		convert = change_shell_var(str2, &idx);
	else if (str2[idx + 1] && (str2[idx + 1] == '_'
			|| ft_isalnum(str2[idx + 1])))
		convert = change_env_var(str2, &idx, info);
	*i += idx - 1;
	return (convert);
}

char	*convert_str(t_info *info, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str);
	while (tmp[i])
	{
		check_quote_flag(tmp[i], info);
		if (!(info->quote & SQ) && tmp[i] == '$')
		{
			if (tmp[i + 1] && (ft_isquote(tmp[i + 1])
					|| tmp[i + 1] == '?' || tmp[i + 1] == '_'
					|| ft_isalnum(tmp[i + 1])))
				tmp = convert_str1(tmp, &i, info);
		}
		i++;
	}
	return (tmp);
}

char	**convert_env(char **arr, t_info *info)
{
	int		i;
	int		count;
	char	**new;

	i = 0;
	count = count_arr(arr);
	new = (char **)ft_calloc(count + 1, sizeof(char *));
	while (arr[i])
	{
		new[i] = convert_str(info, arr[i]);
		i++;
	}
	return (new);
}
