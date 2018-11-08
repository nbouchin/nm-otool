/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sym_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:40:20 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 16:15:52 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void			process_symtab(t_metadata *mdata,
		t_mach_header_64 const *mach_header_64,
		t_load_command *lcommand,
		int flag)
{
	if (flag == 0)
	{
		mdata->symtab = get_symtab(lcommand, mach_header_64);
		print_symtab(lcommand, mach_header_64, mdata);
	}
	else if (flag == 1)
	{
		mdata->symtab = get_big_symtab(lcommand, mach_header_64);
		print_big_symtab(lcommand, mach_header_64, mdata);
	}
	(mdata->symtab) ? free(mdata->symtab) : 0;
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
