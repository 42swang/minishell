/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:35:55 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 14:43:14 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_term(void)
{
	tcgetattr(0, &(g_glovar.origin_term));
	tcgetattr(0, &(g_glovar.gaepo_term));
}

void	set_term(void)
{
	g_glovar.gaepo_term.c_lflag &= ECHO;
	g_glovar.gaepo_term.c_cc[VMIN] = 1;
	g_glovar.gaepo_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &(g_glovar.gaepo_term));
}

void	back_term(void)
{
	tcsetattr(0, TCSANOW, &(g_glovar.origin_term));
}
