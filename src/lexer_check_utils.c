/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:19:21 by swang             #+#    #+#             */
/*   Updated: 2021/12/06 21:54:40 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_check_cmd(t_info *info, int i)
{
	// real이 1이 아니니까 여기 온 이상 리다이렉션 기호는 아님
	if (i == 0)
	{
		info->real[i] = 2;
		return (1);
	}
	// 인덱스가 최소 1이상이면서 바로 앞의 토큰이 파이프이면 그 다음은 명령어
	// (역시 여기 들어온 이상 리다이렉션은아님)
	if (i > 0 && info->token[i - 1][0] == '|')
	{
		info->real[i] = 2; // 2로 기록해둬서 옵션에서 찾기 편하게
		return (1);
	}
	else if (i > 1 && ((info->token[i - 2][0] == '>') || (info->token[i - 2][0] == '<')))
	{
		//인덱스가 최소 2이상이면서 앞앞의 토큰이 리다이렉션
		info->real[i] = 2;
		return (1);
	}
	else
		return (0);
}


int ft_check_opt(char *tok, t_info *info, int i)
{
	// 앞의 토큰이 명령어이면서 str이 -로 시작하면 일단 옵션으로 취급

	//옵션은 젤앞에 안옴
	if (i == 0)
		return (0);
	// 앞에 cmd이면서 i는 최소 1이상이고-> 항상 붙어오는게 아님
	// 첫글자가 -로 시작하면 옵션취급
	// 앞에 옵션이면서 첫글자가 -로 시작하면 역시 옵션
	if (앞이 리다이렉션이면?)
	if (i > 0 && (info->real[i - 1] == 2 || info->real[i - 1] == 3))
	{
		if (*tok == '-')
		{
			info->real[i] = 3;
			return (1);
		}
		return (0);
	}
	else
		return (0);
}

int ft_check_file(t_info *info, int i)
{
	/*
	앞에 아무것도 없으면 이미 위에있는 cmd에 걸러졌으니 i값은 1이상일것
	파일이 맨 처음에 오는 경우가 있을까?
	찐 리다이렉션인지 찾아서 return 1
	*/

	if (info->real[i - 1] == 1)
	{
		// 내앞에가 찐 기호이면서 <이나 >로 시작하는 토큰일경우 리다이렉션이라고 판단.
		if (info->token[i - 1][0] == '<' || info->token[i - 1][0] == '>')
			return (1);
		else
			return (0);
	}
	return (0);
}


void	ft_check_inout(t_info *info, char *tok)
{
	if (info->lex_list->tail->type == IN_RE)
		make_lex_node(IN_FILE, info, tok);
	else if (info->lex_list->tail->type == OUT_RE)
		make_lex_node(OUT_FI, info, tok);
	else if (info->lex_list->tail->type == HEREDOC)
		make_lex_node(HERE_FILE, info, tok);
	else if (info->lex_list->tail->type == OUT_RE2)
		make_lex_node(OUT_FI2, info, tok);
}

/*
 어?
 ..
 ...
 렉서노드 tail이 in_re이면서 내가 명령어도 아니라면 나는 infile아닌가?
*/