#include "../include/minishell.h"

int sin_lex(t_lexical_list *lex)
{
	int i;
	char c;

	if (lex->head->type != 2 || lex->tail->type != 2)
		return (1);
	while (lex->curr != lex->head)
	{
		if (lex->curr->type == -1)
			return (1);
		if (lex->curr->type == PIPE)
		{
			if (lex->curr->next->type == PIPE)
				return (1);
		}
		else
			;
		lex->curr = lex->curr->next;
	}
	return (0);
}

// cat > c > a 될텐데.. | |만 일단 검사함

int sin_error(char *line)
{
	int x;
	int i;
	int y;

	x = 0;
	i = 0;
	y = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{	x++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] == '\'')
				x++;
		}
		else if (line[i] == '\"')
		{	y++;
			while (line[i] && line[i] != '\"')
				i++;
			if (line[i] == '\"')
				y++;
		}
		i++;
	}
	if ((x /= 2) || (y /= 2))
		return (1);
	i = 0;
	while (line[i])
	{
		if (i == 0 || (line[i] == '|' && (!(line[i + 1]) || line[i + 1] != ' ')))
			return (1);
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (!(line[i + 1]))
				return (1);
			if (line[i + 1] != ' ')
			{
				if (!(line[i + 2]) || line[i + 1] != line[i] || line[i + 2] != ' ')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

// '개수 짝수 아니면 에러처리 하지만 \'이랗게 들어오면 (\')는 문자라고 생각하고 '개수로 안셈
// "도 마찬가지
// |는 딱 |만 존재해야함 다만 뒤에 아무것도 없는 |면 에러처리 (뒤에 명령어가 없는걸,,) 그리고 무조건 |뒤에는 공백이 필요.
// <은 << > >> 만 가능 그리고 뒤에 무조건 공백

//' "문제만 해결되면 토큰화에는 문제 없을것으로 판단 남은 신에러는 밑으로

//https://epicarts.tistory.com/163 참조 만들다보니 개간단하게 해버림..?
//str: [ls, -al, <, a, |, grep, "", NULL] 
//type: [WORD, WORD, REDIRECT, WORD, PIPE, WORD, WORD, NULL]
//lex를 word redirect pie로 나눔, 다만 ls나 grep 부분을 word에 포함하지 않고 다르게 나눈다면 다시 수정필요.. 사실 몇분컷이니 의미변동은 마음대로 해도 ㄱㅊ
// 렉서 처러가 끝난후에 |와서< << > >> 가 맨앞이나 뒤에오는지, | <들이 연속으로 나오는지 그외 문법은 딱히? 없는듯? 싶어서 새로 생각나면 바로 추가
// 이건 신텍스 에러긴해도 렉서이후로 진핼됨.

// 놈은,, 미래의 내가 맞추겠지,,

/*

run_parsing.c  파일에 이런식으로 추가해야할듯

t_parse_list *run_parsing(char *line, t_info *info)
{
	t_lexical_list lex;

	if (sin_error(line))
		return (-1);
	info->token = get_token(line);
	if (sin_lex(&lex))
		return (-1);
	return (0); //임시로 종료시키려고 추가
	//return(이 함수의 반환값은 실행단위가 저장된 parse_list);
}
*/
