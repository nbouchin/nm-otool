/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:55:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 13:41:06 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void			print_symtab(t_load_command const *lc,
		t_mach_header_64 const *mach_header_64, t_metadata const *md)
{
	uint32_t		i;
	char			*st;

	i = -1;
	if (is_out((char *)mach_header_64 + ((t_symtab_command*)lc)->stroff))
		return ;
	st = ((char *)mach_header_64 + ((t_symtab_command*)lc)->stroff);
	while (++i < ((t_symtab_command*)lc)->nsyms)
	{
		if (is_64bits(mach_header_64->magic))
		{
			if (is_out((char *)st + md->symtab[i].n_un.n_strx))
				return ;
			gsym_64(md->symtab[i].n_value, get_st(st, md, i), md, i);
		}
		else
		{
			if (is_out((char *)st + (md->symtab)[i].n_un.n_strx))
				return ;
			get_symbol((md->symtab)[i].n_value, get_st(st, md, i), md, i);
		}
	}
}

void			print_big_symtab(t_load_command const *lc,
		t_mach_header_64 const *mach_header_64, t_metadata const *md)
{
	uint32_t		i;
	char			*stable;

	i = -1;
	if (is_out((char *)mach_header_64 + swi(((t_symtab_command*)lc)->stroff)))
		return ;
	stable = ((char *)mach_header_64 + swi(((t_symtab_command*)lc)->stroff));
	while (++i < swi(((t_symtab_command*)lc)->nsyms))
	{
		if (is_64bits(mach_header_64->magic))
		{
			if (is_out(bst(stable, md, i)))
				return ;
			gsym_64(swi(md->symtab[i].n_value), bst(stable, md, i), md, i);
		}
		else
		{
			if (bst(stable, md, i))
				return ;
			get_symbol(swi((md->symtab)[i].n_value), bst(stable, md, i), md, i);
		}
	}
}

t_nlist_64		*get_big_symtab(t_load_command const *lc,
		t_mach_header_64 const *mh)
{
	uint32_t			i;
	t_nlist_64			*nlist;
	t_nlist_64			*st;

	i = -1;
	if (is_out((char *)mh + swi(((t_symtab_command*)lc)->symoff)))
		return (NULL);
	nlist = (t_nlist_64 *)((char *)mh + swi(((t_symtab_command*)lc)->symoff));
	st = ft_memalloc(swi(((t_symtab_command*)lc)->nsyms) * sizeof(t_nlist_64));
	while (++i < swi(((t_symtab_command*)lc)->nsyms))
	{
		st[i] = *nlist;
		if (is_64bits(mh->magic))
		{
			if (is_out((char*)(nlist++ + 1)))
				return (NULL);
		}
		else
		{
			if (is_out((char*)(t_nlist*)(nlist + 1)))
				return (NULL);
			nlist = (t_nlist_64*)((t_nlist*)nlist + 1);
		}
	}
	return (st);
}

t_nlist_64		*get_symtab(t_load_command const *lc,
		t_mach_header_64 const *mh)
{
	uint32_t			i;
	t_nlist_64			*nlist;
	t_nlist_64			*symtab;

	i = -1;
	if (is_out((char*)mh + ((t_symtab_command*)lc)->symoff))
		return (NULL);
	nlist = (t_nlist_64 *)((char *)mh + ((t_symtab_command*)lc)->symoff);
	symtab = ft_memalloc(((t_symtab_command*)lc)->nsyms * sizeof(t_nlist_64));
	while (++i < ((t_symtab_command*)lc)->nsyms)
	{
		symtab[i] = *nlist;
		if (is_64bits(mh->magic))
		{
			if (is_out((char *)nlist++ + 1))
				return (NULL);
		}
		else
		{
			if (is_out((char *)(t_nlist*)nlist + 1))
				return (NULL);
			nlist = (t_nlist_64*)((t_nlist*)nlist + 1);
		}
	}
	return (symtab);
}
