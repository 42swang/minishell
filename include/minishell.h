/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:32:43 by swang             #+#    #+#             */
/*   Updated: 2021/11/20 17:55:09 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/* readline 함수, add_history함수, exit, printf, 동적할당 */

typedef struct s_lexical_node
{
	int		type;
	char	*value;
}	t_lexical_node;

typedef struct s_lexical_list
{
	t_lexical_node	*prev;
	t_lexical_node	*next;
	t_lexical_node	*curr;
}	t_lexical_list;





#endif