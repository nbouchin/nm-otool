/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:31:07 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/09 14:11:46 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void	swap_val(t_metadata const *md, size_t i)
{
	t_nlist_64			swap;

	swap = md->symtab[i];
	md->symtab[i] = md->symtab[i + 1];
	md->symtab[i + 1] = swap;
}

void	sort_symtab(char *st, t_metadata const *md, size_t size)
{
	size_t				i;
	size_t				j;

	i = 0;
	j = size - 1;
	while (j)
	{
		i = 0;
		while (i < j)
		{
			if (ft_strcmp(get_st(st, md, i), get_st(st, md, i + 1)) > 0)
				swap_val(md, i);
			else if (ft_strcmp(get_st(st, md, i),
				get_st(st, md, i + 1)) == 0)
			{
				if (md->symtab[i].n_value >= md->symtab[i + 1].n_value)
					swap_val(md, i);
			}
			i++;
		}
		j--;
	}
}

void	sort_big_symtab(char *st, t_metadata const *md, size_t size)
{
	size_t				i;
	size_t				j;

	i = 0;
	j = size - 1;
	while (j)
	{
		i = 0;
		while (i < j)
		{
			if (ft_strcmp(bst(st, md, i), bst(st, md, i + 1)) > 0)
				swap_val(md, i);
			else if (ft_strcmp(bst(st, md, i), bst(st, md, i + 1)) == 0)
			{
				if (swi(md->symtab[i].n_value)
					>= swi(md->symtab[i + 1].n_value))
					swap_val(md, i);
			}
			i++;
		}
		j--;
	}
}
