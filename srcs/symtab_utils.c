/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:55:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/26 11:14:13 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

void		print_symbol(uint64_t const n_value, char const letter,
		char const *symname, int const arch_type)
{
	if (arch_type == 64)
		(letter == 'U' || letter == 'u')
			? ft_printf("%-16c %c %s\n", ' ', letter, symname)
			: ft_printf("%016llx %c %s\n", n_value, letter, symname);
	else if (arch_type == 32)
		(letter == 'U' || letter == 'u')
			? ft_printf("%-8c %c %s\n", ' ', letter, symname)
			: ft_printf("%08llx %c %s\n", (uint32_t)n_value, letter, symname);
}

char		get_type_char(t_metadata const *mdata, int const i)
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
	else if (!ft_strcmp(mdata->sectab[mdata->symtab[i].n_sect - 1].sectname,
				SECT_COMMON))
		to_ret = 'c';
	return (to_ret);
}

void		get_symbol_64(uint64_t const n_value, char const *symbol_name,
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
		print_symbol(n_value, letter, symbol_name, 64);
}

void		get_symbol(uint64_t const n_value, char const *symbol_name,
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
		print_symbol(n_value, letter, symbol_name, 32);
}

void		print_big_symtab(t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64, t_metadata const *mdata)
{
	uint32_t		i;
	char			*stable;

	i = -1;
	stable = (char *)((char *)mach_header_64 +
			OSSwapInt32(((t_symtab_command*)load_command)->stroff));
	while (++i < OSSwapInt32(((t_symtab_command*)load_command)->nsyms))
	{
		if (is_64bits(mach_header_64->magic))
			get_symbol_64(OSSwapInt32(mdata->symtab[i].n_value), (char *)stable
					+ OSSwapInt32(mdata->symtab[i].n_un.n_strx), mdata, i);
		else
			get_symbol(OSSwapInt32(((t_nlist*)mdata->symtab)[i].n_value),
			(char*)stable +
			OSSwapInt32(((t_nlist*)mdata->symtab)[i].n_un.n_strx), mdata, i);
	}
}

void		print_symtab(t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64, t_metadata const *metadata)
{
	uint32_t		i;
	char			*string_table;

	i = -1;
	string_table = (char *)((char *)mach_header_64 +
	((t_symtab_command*)load_command)->stroff);
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		if (is_64bits(mach_header_64->magic))
			get_symbol_64(metadata->symtab[i].n_value, (char *)string_table
			+ metadata->symtab[i].n_un.n_strx, metadata, i);
		else
			get_symbol((metadata->symtab)[i].n_value, (char *)string_table
			+ (metadata->symtab)[i].n_un.n_strx, metadata, i);
	}
}

t_nlist_64		*get_big_symtab(t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64)
{
	uint32_t			i;
	t_nlist_64			*nlist_64;
	t_nlist_64			*symtab;

	i = -1;
	nlist_64 = (t_nlist_64 *)((char *)mach_header_64
	+ OSSwapInt32(((t_symtab_command*)load_command)->symoff));
	symtab = malloc(OSSwapInt32(((t_symtab_command*)load_command)->nsyms)
	* sizeof(t_nlist_64));
	while (++i < OSSwapInt32(((t_symtab_command*)load_command)->nsyms))
	{
		symtab[i] = *nlist_64;
		nlist_64 += 1;
	}
	return (symtab);
}

t_nlist_64		*get_symtab(t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64)
{
	uint32_t			i;
	t_nlist_64			*nlist_64;
	t_nlist_64			*symtab;

	i = -1;
	nlist_64 = (t_nlist_64 *)((char *)mach_header_64
	+ ((t_symtab_command*)load_command)->symoff);
	symtab = malloc(((t_symtab_command*)load_command)->nsyms
	* sizeof(t_nlist_64));
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		symtab[i] = *nlist_64;
		if (is_64bits(mach_header_64->magic))
			nlist_64++;
		else
			nlist_64 = (t_nlist_64*)((t_nlist*)nlist_64 + 1);
	}
	return (symtab);
}
