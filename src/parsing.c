/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:51:11 by swang             #+#    #+#             */
/*   Updated: 2022/01/23 22:56:03 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing(char *line, t_info *info)
{
	info->token = run_tokenizer(line, info);
	info->lex_list = run_lexer(info);
	info->parse_list = run_parser(info);
	if (sin_lex(info->lex_list))
		return (-1);
	return (0);
}
