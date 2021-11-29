#include "../include/minishell.h"

t_parse_node set_parse(t_lexical_list lex, int i, t_parse_list parse, int no_i)
{
	int idx;
	t_parse_node no;
	int c;

	idx = 0;
	while (idx == i)
	{
		lex.curr = lex.curr->prev;
		idx++;
	}
	no.index = no_i;
	no.p_fd[0] = 0;
	no.p_fd[1] = 0;
	c = 0;
	while (idx)
	{
		no.cmd[c] = lex.curr->value;
		no.lex[c] = lex.curr->type;
		lex.curr = lex.curr->next;
		idx--;
		c++;
	}
	no.cmd[c] = 0;
	no.lex[c] = 0;
	return (no);
}

t_parse_list get_parse(t_lexical_list lex)
{
	t_parse_list parse;
	int i;
	int no_i;

	i = 0;
	no_i = 0;
	while (lex.curr == lex.head)
	{
		if (lex.curr->type = PIPE)
		{
			set_parse(lex, i, parse, no_i);
			i = -1;
			no_i++;
		}
		i++;
		lex.curr = lex.curr->next;
	}
	set_parse(lex, 0, parse, no_i); //마지막 parse 0, 0인거 추가함 지워도 상관은 없음 혹시나 해서 추가,,
	return (parse);
}

void init_parse(t_parse_list parse)
{
	parse.head = 0;
	parse.curr = 0;
	parse.tail = 0;
}