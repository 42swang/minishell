/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:59:22 by swang             #+#    #+#             */
/*   Updated: 2021/11/25 21:35:53 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**run_tokenizer(char *line, t_info *info)
{
	char	**arr;

	arr = divide_line(line, info);
	convert_env(arr, info);
	trim_quote(arr, info);
	return (arr);
}
