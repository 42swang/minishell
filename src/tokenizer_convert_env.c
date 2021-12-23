/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_convert_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:31:17 by swang             #+#    #+#             */
/*   Updated: 2021/12/24 05:52:37 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*change_shell_var(char *str, int *idx, t_info *info)
{
	int		len;
	char	*head;
	char	*tail;
	char	*ret;

	len = 0;
	ret = 0;
	if (ft_strncmp(str, "$?", 2) == 0)
	{
		head = ft_itoa(info->exit_stat);
		len = ft_strlen(head);
		tail = ft_substr(str, 2, ft_strlen(str) - 2);
		ret = ft_strjoin(head, tail);
		free(head);
		free(tail);
	}
	*idx += len;
	return (ret);
}

static char	*change_env_var(char *str2, int *idx, t_info *info)
{
	t_env_node	*p;
	int		len;
	char	*head;
	char	*tail;
	char	*ret;

	p = info->env_list->head;
	//str[idx] = $
	*idx += 1;
	len = *idx;
	while (ft_isalnum(str2[*idx]) == 1 || str2[len] == '_')
		*idx += 1;
	//idx는 지금 환경변수로 추정되는 단어의 끝 + 1의 위치임.
	len = *idx - len;
	//원래 문자열에서 달러사인까지의 길이 + 환경변수이름으로 추정되는 부분 - 원래문자열에서 달러사인까지의 길이 = 환경변수이름으로 추정되는 부분의 길이
	while (p)
	{
		if ((len == (int)ft_strlen(p->env_arr[0])) && (ft_strncmp(str2 + 1, p->env_arr[0], len) == 0))
		{ //(이름으로 추정되는 길이 == 환경변수이름이 같고, 두 문자열이 같을 때)
			head = p->env_arr[1];
			tail = ft_substr(str2 + 1, len, ft_strlen(str2 + len));
			ret = ft_strjoin(head, tail);
			free(tail);
			return (ret);
		}
		p = p->next;
	}
	//환경변수랑 겹치는 게 없을땐 빈문자열반환 (이상한환경변수는 사라짐)
	ret = ft_substr(str2 + 1, len, ft_strlen(str2 + len));
	*idx = 0;
	return (ret);
}

int	count_arr(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*convert_str2(char *str2, int *i, t_info *info)
{
	char	*convert;
	int		idx;

	idx = 0;
	convert = 0;
	// 제거 / $? / 환경
	if (str2[idx + 1] && (ft_isquote(str2[idx + 1])))
		convert = ft_substr(str2, 1, ft_strlen(str2));
	else if (str2[idx + 1] && str2[idx + 1] == '?')
		convert = change_shell_var(str2, &idx, info);
	else if (str2[idx + 1] && (str2[idx + 1] == '-' || ft_isalnum(str2[idx + 1])))
		convert = change_env_var(str2, &idx, info);
	else
		printf("in tokenizer_convert_env.c : add convert test\n");
	*i += idx - 1;
	//$USER$USER i = 0 에서 치환이 완료되면
	//치환된문자열의 끝부분을 가리키고 있어야함
	return (convert);
}

char *convert_str(t_info *info, char *str)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str);
	while (tmp[i])
	{
		check_quote_flag(tmp[i], info); //sq가 켜져있으면 치환 ㄴ
		if (!(info->quote & SQ) && tmp[i] == '$')
		{
			// $ + 따옴표 = 제거,  vs 그냥
			if (tmp[i + 1] && (ft_isquote(tmp[i + 1]) || tmp[i + 1] == '?' || tmp[i + 1] == '-' || ft_isalnum(tmp[i + 1])))
			{
				//	치환/제거하고 변경된 i를 받을 수 있도록, 한번에 하나의 환경변수만 처리
				s1 = ft_substr(tmp, 0 , i);
				s2 = convert_str2(tmp + i, &i, info);// 얘는 치환 + 그 뒤에있는거
				ft_free(&tmp);
				tmp = ft_strjoin(s1, s2);
				ft_free(&s1);
				ft_free(&s2);
			}
		}
		i++;
	}
	return (tmp);
}

char	**convert_env(char **arr, t_info *info)
{
	int	i;
	int	count;
	char	**new;

	i = 0;
	count = count_arr(arr);
	new = (char **)ft_calloc(count + 1, sizeof(char *));
	while(arr[i])
	{
		new[i] = convert_str(info, arr[i]);
		i++;
	}
	return (new);
}
