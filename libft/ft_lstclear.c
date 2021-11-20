/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 01:46:21 by swang             #+#    #+#             */
/*   Updated: 2021/04/01 15:11:12 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*tmp;

	p = *lst;
	if (!p)
		return ;
	while (p != 0)
	{
		tmp = p->next;
		ft_lstdelone(p, del);
		p = tmp;
	}
	*lst = NULL;
}
