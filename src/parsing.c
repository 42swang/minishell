/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:51:11 by swang             #+#    #+#             */
/*   Updated: 2022/01/21 14:21:48 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing(char *line, t_info *info)
{
	info->token = run_tokenizer(line, info);
//	system("leaks minishell");
	info->lex_list = run_lexer(info);
//	system("leaks minishell");
	info->parse_list = run_parser(info);
//	system("leaks minishell");
	if (sin_lex(info->lex_list))
		return (-1);
	return (0);
}
