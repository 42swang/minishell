#include "../include/minishell.h"

int ft_echo(t_parse_node *p, t_info *info)
{
	int		i;
	int		n_option;

	(void)info;
	i = 0;
	n_option = 0;
	while (p->cmd[i])
	{
		if (p->lex[i] == OPT)
			n_option = 1;
		else if (p->lex[i] == ARG)
		{
			ft_putstr_fd(p->cmd[i], 1);
			if (p->cmd[i + 1] && p->cmd[i][0] != '\0')
				write(1, " ", 1);
		}
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}