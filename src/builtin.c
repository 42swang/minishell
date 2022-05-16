/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:06:41 by swang             #+#    #+#             */
/*   Updated: 2022/01/24 14:43:24 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isbuiltin(char *tok)
{
	if (ft_strncmp(tok, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tok, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tok, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(tok, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(tok, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(tok, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(tok, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

int	sort_builtin(char *cmd, t_parse_node *p, t_info *info, int i)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd, "echo", 5) == 0)
		ret = ft_echo(p, info);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ret = ft_cd(p, info);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		ret = ft_pwd(p, info);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		ret = ft_exit(p, info);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		ret = ft_env(info);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ret = ft_unset(info, p, i);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ret = ft_export(info, p, i);
	return (ret);
}

void	run_builtin(t_parse_node *p, t_info *info)
{
	char	*cmd;
	int		ret;
	int		i;
	int		in_fd;
	int		out_fd;

	ret = 0;
	i = 0;
	in_fd = dup(0);
	out_fd = dup(1);
	redirection(info, p);
	while (p->lex[i] && p->lex[i] != CMD)
		i++;
	cmd = p->cmd[i];
	ret = sort_builtin(cmd, p, info, i);
	dup2(in_fd, 0);
	dup2(out_fd, 1);
	g_glovar.g_exit_status = ret;
}
