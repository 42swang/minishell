/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_convert_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:31:17 by swang             #+#    #+#             */
/*   Updated: 2021/11/25 22:11:38 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*change_shell_var(char *str, t_info *info)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*ret;

	i = 0;
	ret = 0;
	if (ft_strncmp(str, "$?", 2) == 0)
	{
		s1 = ft_itoa(info->exit_stat);
		s2 = ft_substr(str, 2, ft_strlen(str) - 2);
		ret = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return (ret);
}

static char	*change_env_var(char *str, t_info *info)
{
	t_env_node	*p;
	int		len;
	char	*s1;
	char	*s2;
	char	*ret;

	p = info->env_head;
	len = 0;
	while (p != 0)
	{
		//len = 문자열 str에서 띄어쓰기나 기타등등 환경변수인부분
		while (ft_isalnum(str[len]) == 1 || str[len] == '_')
			len++;
		if (!(ft_strncmp(str, p->env_arr[0], len)))
		{
			s1 = p->env_arr[1];
			s2 = ft_substr(str, len, ft_strlen(str + len));
			ret = ft_strjoin(s1, s2);
			free(s2);
			return (ret);
		}
		p = p->next;
	}
	//환경변수랑 겹치는 게 없을땐 빈문자열반환 (이상한환경변수는 사라짐)
	ret = ft_strdup("");
	return (ret);
}

void	convert_env(char **arr, t_info *info)
{
	// 작은따옴표 안에있느건 무시해야함
	int	i;
	int	j;
	char	*s1;
	char	*s2;
	char	*temp;

	i = 0;
	while(arr[i])
	{
		j = 0;
		while(arr[i][j])
		{
			check_quote_flag(arr[i][j], info); //sq가 켜져있으면 치환 ㄴ
			if (!(info->quote & SQ) && arr[i][j] == '$' && (ft_isalpha(arr[i][j + 1]) == 1 || arr[i][j + 1] == '?' || arr[i][j + 1] == '_'))
			{
				s1 = ft_substr(arr[i], 0, j);
				if (arr[i][j + 1] == '?')
					s2 = change_shell_var(arr[i] + j, info);
				else
					s2 = change_env_var(arr[i] + j + 1, info);
				temp = arr[i];
				arr[i] = ft_strjoin(s1, s2);
				free(s1);
				free(s2);
				free(temp);
			}
			j++;
		}
		i++;
	}
}

/*
	p = info->env_head;
	while (p != 0)
	{
		printf("	[%s] : [%s]\n", p->env_arr[0], p->env_arr[1]);
		p = p->next;
	}
*/