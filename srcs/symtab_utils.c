/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:55:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/25 16:32:02 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

void		print_symbol(uint64_t n_value, char letter, char *symbol_name, int arch_type)
{
	if (arch_type == 64)
		(letter == 'U') ? ft_printf("%-16c %c %s\n", ' ', letter, symbol_name)
			: ft_printf("%016llx %c %s\n", n_value, letter, symbol_name);
	else if (arch_type == 32)
		(letter == 'U') ? ft_printf("%-8c %c %s\n", ' ', letter, symbol_name)
			: ft_printf("%08llx %c %s\n", (uint32_t)n_value, letter, symbol_name);
}

char		get_type_char(t_metadata *metadata, int i)
{
	char	to_ret;

	to_ret = 'S';
	if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_TEXT))
		to_ret = 'T';
	else if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_DATA))
		to_ret = 'D';
	else if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_BSS))
		to_ret = 'B';
	else if (!ft_strcmp(metadata->sectab[metadata->symtab[i].n_sect - 1].sectname, SECT_COMMON))
		to_ret = 'C';
	return (to_ret);
}

void		get_symbol_64(uint64_t n_value, char *symbol_name, t_metadata *metadata, int i)
{
	char	letter;

	letter = 0;
	if ((metadata->symtab[i].n_type & N_TYPE) == N_UNDF)
		letter = 'U';
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_ABS)
		letter = 'A';
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_SECT)
		letter = get_type_char(metadata, i);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_INDR)
		letter = 'I';
	else if ((metadata->symtab[i].n_type & N_EXT))
		letter = ft_tolower(letter);
	if (letter != 0)
		print_symbol(n_value, letter, symbol_name, 64);
}

void		get_symbol(uint64_t n_value, char *symbol_name, t_metadata *metadata, int i)
{
	char	letter;

	letter = 0;
	if ((metadata->symtab[i].n_type & N_TYPE) == N_UNDF)
		letter = 'U';
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_ABS)
		letter = 'A';
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_SECT)
		letter = get_type_char(metadata, i);
	else if ((metadata->symtab[i].n_type & N_TYPE) == N_INDR)
		letter = 'I';
	else if ((metadata->symtab[i].n_type & N_EXT))
		letter = ft_tolower(letter);
	if (letter != 0)
		print_symbol(n_value, letter, symbol_name, 32);
}

void		print_big_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64, t_metadata *metadata)
{
	uint32_t		i;
	char			*string_table;

	i = -1; 
	string_table = (char *)((char *)mach_header_64 + OSSwapInt32(((t_symtab_command*)load_command)->stroff));
	while (++i < OSSwapInt32(((t_symtab_command*)load_command)->nsyms))
	{
		if (is_64bits(mach_header_64->magic))
			get_symbol_64(OSSwapInt32(metadata->symtab[i].n_value), (char *)string_table + OSSwapInt32(metadata->symtab[i].n_un.n_strx), metadata, i);
		else
			get_symbol(OSSwapInt32(((t_nlist*)metadata->symtab)[i].n_value), (char *)string_table + OSSwapInt32(((t_nlist*)metadata->symtab)[i].n_un.n_strx), metadata, i);
	}
}

void		print_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64, t_metadata *metadata)
{
	uint32_t		i;
	char			*string_table;

	i = -1;
	string_table = (char *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->stroff);
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		if (is_64bits(mach_header_64->magic))
			get_symbol_64(metadata->symtab[i].n_value, (char *)string_table + metadata->symtab[i].n_un.n_strx, metadata, i);
		else
			get_symbol((metadata->symtab)[i].n_value, (char *)string_table + (metadata->symtab)[i].n_un.n_strx, metadata, i);
	}
}

t_nlist_64		*get_big_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64)
{
	uint32_t			i;
	t_nlist_64			*nlist_64;
	t_nlist_64			*symtab;

	i = -1;
	nlist_64 = (t_nlist_64 *)((char *)mach_header_64 + OSSwapInt32(((t_symtab_command*)load_command)->symoff));
	symtab = malloc(OSSwapInt32(((t_symtab_command*)load_command)->nsyms) * sizeof(t_nlist_64));
	while (++i < OSSwapInt32(((t_symtab_command*)load_command)->nsyms))
	{
		symtab[i] = *nlist_64;
		nlist_64 += 1;
	}
	return (symtab);
}

t_nlist_64		*get_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64)
{
	uint32_t			i;
	t_nlist_64			*nlist_64;
	t_nlist_64			*symtab;

	i = -1;
	nlist_64 = (t_nlist_64 *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->symoff);
	symtab = malloc(((t_symtab_command*)load_command)->nsyms * sizeof(t_nlist_64));
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
