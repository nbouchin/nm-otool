/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:55:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 12:40:03 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void			ft_putnendl(const char *str, size_t length)
{
	size_t		i;

	i = 0;
	while (i < length && str[i])
		ft_putchar(str[i++]);
	ft_putendl("");
}

void			print_symbol_32(uint64_t const n_value, char const letter,
		char const *symname, t_metadata const *metadata)
{
	if (letter == 'U' || letter == 'u')
	{
		ft_printf("%-8c %c ", ' ', letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
	else
	{
		ft_printf("%08llx %c ", (uint32_t)n_value, letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
}

void			print_symbol_64(uint64_t const n_value, char const letter,
		char const *symname, t_metadata const *metadata)
{
	if (letter == 'U' || letter == 'u')
	{
		ft_printf("%-16c %c ", ' ', letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
	else
	{
		ft_printf("%016llx %c ", n_value, letter);
		ft_putnendl((char*)symname, metadata->end - symname);
	}
}

char			get_type_char(t_metadata const *mdata, int const i)
{
	char	to_ret;

	to_ret = 's';
	if (!ft_strcmp(mdata->sectab[mdata->symtab[i].n_sect - 1].sectname,
				SECT_TEXT))
		to_ret = 't';
	else if (!ft_strcmp(mdata->sectab[mdata->symtab[i].n_sect - 1].sectname,
				SECT_DATA))
		to_ret = 'd';
	else if (!ft_strcmp(mdata->sectab[mdata->symtab[i].n_sect - 1].sectname,
				SECT_BSS))
		to_ret = 'b';
	return (to_ret);
}

void			gsym_64(uint64_t const n_value, char const *symbol_name,
		t_metadata const *metadata, int const i)
{
	char	letter;

	letter = 0;
	if ((metadata->symtab[i].n_type & N_STAB))
		letter = 0;
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_UNDF)
	{
		if (n_value && (metadata->symtab[i].n_type & N_EXT))
			letter = 'c';
		else
			letter = 'u';
	}
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_ABS)
		letter = 'a';
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_SECT)
		letter = get_type_char(metadata, i);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_INDR)
		letter = 'i';
	if ((metadata->symtab[i].n_type & N_EXT))
		letter = ft_toupper(letter);
	if (letter != 0)
		print_symbol_64(n_value, letter, symbol_name, metadata);
}

void			get_symbol(uint64_t const n_value, char const *symbol_name,
		t_metadata const *metadata, int const i)
{
	char	letter;

	letter = 0;
	if ((metadata->symtab[i].n_type & N_STAB))
		letter = 0;
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_UNDF)
		letter = 'u';
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_ABS)
		letter = 'a';
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_SECT)
		letter = get_type_char(metadata, i);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_INDR)
		letter = 'i';
	if ((metadata->symtab[i].n_type & N_EXT))
		letter = ft_toupper(letter);
	if (letter != 0)
		print_symbol_32(n_value, letter, symbol_name, metadata);
}

char			*get_st(char *string_table, t_metadata const *metadata, int i)
{
	return ((char *)string_table
					+ metadata->symtab[i].n_un.n_strx);
}

char			*bst(char *string_table,
		t_metadata const *metadata, int i)
{
	return ((char *)string_table
					+ swi(metadata->symtab[i].n_un.n_strx));
}

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
