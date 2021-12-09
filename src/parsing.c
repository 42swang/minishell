/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:51:11 by swang             #+#    #+#             */
/*   Updated: 2021/12/09 15:48:11 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parsing(char *line, t_info *info)
{
	/*
	if (sin_error(line))
		return (-1);
	*/
	info->token = run_tokenizer(line, info);
	run_lexer(info);
	run_parser(info);
	pre_open(info);
	/*
	if (sin_lex(&lex))
		return (-1);
	*/
}