#include "../include/minishell.h"

int ft_pwd(t_parse_node *p, t_info *info)
{
	char	*buf;

	(void)p;
	(void)info;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (-1);
	else
		printf("%s\n", buf);
	free(buf);
	return (0);
}