#include "../include/minishell.h"

void set_lex(int c, t_lexical_list lex, t_info *info, int i)
{
	t_lexical_node no;

	no.type = c;
	no.value = info->token[i];
	if (c <= OUT_RE2 && c >= OUT_RE)
	{
		if (!(info->token[i + 1]))
			no.type = -1;
		no.value = info->token[i + 1];
		i++;
	}
	if (lex.head == 0)
	{
		no.prev = &no;
		no.next = &no;
		lex.head = &no;
		lex.curr = &no;
		lex.tail = &no;
	}
	else
	{
		no.prev = lex.tail;
		no.next = lex.head;
		lex.tail->next = &no;
		lex.tail = &no;                                                                                           
	}
}

int cmd_tok(char *tok)
{
	if (tok == 'echo')
		return (1);
	if (tok == 'cd')
		return (1);
	if (tok == 'pwd')
		return (1);
	if (tok == 'export')
		return (1);
	if (tok == 'unset')
		return (1);
	if (tok == 'env')
		return (1);
	if (tok == 'exit')
		return (1);
	return(0);
}

t_lexical_list get_lex(t_info *info)
{
	char *tok;
	t_lexical_list lex;
	int i;

	i = 0;
	while (info->token[i])
	{
		tok = info->token[i];
		if (info->real[i] == 1)
		{
			if (tok == '|')
				set_lex(PIPE, lex, info, i);
			else if (tok == '>')
				set_lex(OUT_RE, lex, info, i);
			else if (tok == '<')
				set_lex(IN_RE, lex, info, i);
			else if (tok == '>>')
				set_lex(HEREDOC, lex, info, i);
			else if (tok == '<<')
				set_lex(OUT_RE2, lex, info, i);	
		}
		else if (cmd_tok(tok))
			set_lex(CMD, lex, info, i);
		else
			set_lex(ARG, lex, info, i);
		i++;
	}
	return (lex);
}
void init_lex(t_lexical_list lex)
{
	lex.head = 0;
	lex.curr = 0;
	lex.tail = 0;
}