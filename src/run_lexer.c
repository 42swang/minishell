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
	{
		return(0);
		printf("in isbuiltin\n");
	}
}

void	make_lex_node(int type, t_info *info, char *tok)
{
	t_lexical_node *new;

	new = (t_lexical_node *)ft_calloc(1, sizeof(t_lexical_node));
	if (!new)
		exit(0); //임시로 탈출
	new->type = type;
	new->value = tok;
	if (info->lex_list->head == 0)
	{
		info->lex_list->head = new;
		info->lex_list->tail = new;
	}
	else
	{
		info->lex_list->tail->next = new;
		new->prev = info->lex_list->tail;
		info->lex_list->tail = new;
	}
	new = 0;
}

void	get_lex(t_info *info)
{
	int		i;
	char	*tok;

	i = 0;
	while (info->token[i])
	{
		tok = info->token[i];
		if (info->real[i] == 1)
		{
			if (tok[0] == '|')
				make_lex_node(PIPE, info, tok);
			else if (ft_strncmp(tok, ">>", 2) == 0)
				make_lex_node(OUT_RE2, info, tok);
			else if (ft_strncmp(tok, "<<", 2) == 0)
				make_lex_node(HEREDOC, info, tok);
			else if (tok[0] == '>')
				make_lex_node(OUT_RE, info, tok);
			else if (tok[0] == '<')
				make_lex_node(IN_RE, info, tok);
		}
		else if (ft_isbuiltin(tok) == 1)
			make_lex_node(CMD, info, tok);
		else
			make_lex_node(ARG, info, tok);
		i++;
	}
}

t_lexical_list *run_lexer(t_info *info)
{
	t_lexical_list *lex;
	
	lex = (t_lexical_list *)ft_calloc(1, sizeof(t_lexical_list));
	info->lex_list = lex;
	get_lex(info);
	return (lex);
}

void init_lex(t_lexical_list *lex)
{
	lex->head = 0;
	lex->curr = 0;
	lex->tail = 0;
}