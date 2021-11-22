/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:51:11 by swang             #+#    #+#             */
/*   Updated: 2021/11/21 01:31:12 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
1. 토큰으로 쪼개기

2. 토큰에 의미 부여하기

3. 의미 부여된 토큰들을 가지고 실행단위리스트 만들기


이 함수의 반환값은 실행단위가 저장된 parse_list);

*/

t_parse_list *run_parsing(char *line, t_info *info)
{
	t_lexical_list lex;

	if (sin_error(line))
		return (-1);
	info->token = get_token(line);
	if (sin_lex(&lex))
		return (-1);
	return (0); //임시로 종료시키려고 추가
	//return(이 함수의 반환값은 실행단위가 저장된 parse_list);
}