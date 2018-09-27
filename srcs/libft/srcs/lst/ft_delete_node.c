/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:41:49 by nbouchin          #+#    #+#             */
/*   Updated: 2017/07/27 14:33:58 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Remove node from list and free it
*/

void	delete_node(t_list *head, t_list *n)
{
	t_list	*prev;

	if (head == n)
	{
		if (head->nxt == NULL)
			free_node(n);
		head->cont = head->nxt->cont;
		n = head->nxt;
		head->nxt = head->nxt->nxt;
		free(n);
		return ;
	}
	prev = head;
	while (prev->nxt != NULL && prev->nxt != n)
		prev = prev->nxt;
	if (prev->nxt == NULL)
		return ;
	prev->nxt = prev->nxt->nxt;
	free(n);
	return ;
}
