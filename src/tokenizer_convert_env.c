/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_convert_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:31:17 by swang             #+#    #+#             */
/*   Updated: 2021/12/10 19:47:21 by swang            ###   ########.fr       */
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

//------------------------------아래 새로운 함수---

static char	*change_env_var(char *str, int *idx, t_info *info)
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
	while (ft_isalnum(str[*idx]) == 1 || str[len] == '_')
		*idx += 1;
	len = *idx - len;
	if (len == (int)ft_strlen(p->env_arr[0]) && !(ft_strncmp(str, p->env_arr[0], len)))
	{

			head = p->env_arr[1];
			tail = ft_substr(str, len, ft_strlen(str + len));
			ret = ft_strjoin(head, tail);
			free(s2);
			return (ret);
	}
		p = p->next;
	}
	//환경변수랑 겹치는 게 없을땐 빈문자열반환 (이상한환경변수는 사라짐)
	ret = ft_substr(str, len, ft_strlen(str + len));
	return (ret);
}


static char	*trim_sign(char *str, int *idx)
{
	//$"ㅁㅇㄹ" 이렇게 들어오면 $ 제거해주기
	char	*head;
	char	*tail;
	char	*ret;

	head = ft_substr(str, 0, *idx);
	tail = ft_substr(str, *idx + 1, ft_strlen(str + (*idx) + 1));
	ret = ft_strjoin(head, tail);
	free (head);
	free (tail);
	*idx -= 1;
	return (ret);
}

static char	*convert_env2(char *str, int *i, t_info *info)
{
	char	*head;
	char	*convert;
	char	*new;
	int		idx;

	idx = *i;
	// 제거 / $? / 환경
	head = ft_substr(str, 0, *i);
	if (str[idx + 1] && (ft_isquote(str[idx + 1])))
		convert = trim_sign(str, &idx);
	else if (str[idx + 1] && str[idx + 1] == '?')
		convert = change_shell_var(str, &idx, info);
	else if (str[idx + 1] && (str[idx + 1] == '-' || ft_isalnum(str[idx + 1])))
		convert = change_env_var(str[idx], &idx, info);
	else
		ft_strendl_fd("convert_env2 케이스 추가\n");
	new = ft_strjoin(head, convert);
	*i = idx;
	//$USER$USER i = 0 에서 치환이 완료되면, 5를 가리키고 있어야함
	return (con);
}

char	*convert_env(char *str, t_info *info)
{
	// 작은따옴표 안에있느건 무시해야함
	// 환경변수를 치환한 새로운 토큰 한개만 리턴
	int	i;
	char	*s1;
	char	*s2
	char	*tmp;

	i = 0;
	while(str[i])
	{
		check_quote_flag(str[i], info); //sq가 켜져있으면 치환 ㄴ
		if (!(info->quote & SQ) && str[i] == '$')
		{
			// $ + 따옴표 = 제거,  vs 그냥
			if (str[i + 1] && (ft_isquote(str[i + 1]) || str[i + 1] == '?' || str[i + 1] == '-' || ft_isalnum(str[i])))
			{
				tmp = new;
				//	치환/제거하고 변경된 i를 받을 수 있도록, 한번에 하나의 환경변수만 처리
				s1 = ft_substr(str, 0 , i);
				s2 = convet_env2(str + i, &i, info);
				if (tmp)
					free(tmp);
			}
			// if문에 해당 안되면 그냥 문자열 처리하고 넘어감
		}
		i++;
	}
	return (new);
}

/*
//	asdfadf$dahj"kla"$ADFSAA$ssdf 이렇게 있을 때
	head{asdfadf} / 치환함수($dahj"kla"$ADFSAA$ssdf)
					치환($dahj) / tail{"kla"$ADFSAA$ssdf}

*/
