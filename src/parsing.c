/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:51:11 by swang             #+#    #+#             */
/*   Updated: 2022/01/19 16:31:05 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
void	parsing(char *line, t_info *info)
{
	if (sin_error(line))
		return (-1);
	info->token = run_tokenizer(line, info);
	info->lex_list = run_lexer(info);
	info->parse_list = run_parser(info);
	//ft_print_lex_list(info);
//	ft_print_str_arr(info->token);
//	ft_print_parse_list(info);
	if (sin_lex(&lex))
		return (-1);
}*/

int	parsing(char *line, t_info *info)
{
	info->token = run_tokenizer(line, info);
	//ft_print_str_arr(info->token);
	info->lex_list = run_lexer(info);
	info->parse_list = run_parser(info);
	//ft_print_parse_list(info);
	if (sin_lex(info->lex_list))
		return (-1);
	return (0);
}
