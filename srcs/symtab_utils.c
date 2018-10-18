/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:55:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/18 17:14:53 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

void		print_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64, t_nlist_64 *symtab)
{
	uint32_t		i;
	t_nlist_64		*nlist_64;
	char			*string_table;

	i = -1;
	if (mach_header_64->magic != MH_MAGIC)
	{
		nlist_64 = (t_nlist_64 *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->symoff);
		string_table = (char *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->stroff);
		while (++i < ((t_symtab_command*)load_command)->nsyms)
		{
			if ((symtab[i].n_type & N_STAB))
				;//		ft_printf("%017llx %c %s\n", symtab[i].n_value, 'S', (char *)string_table + symtab[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_UNDF)
				ft_printf("%-17c %c %s\n", ' ', 'U', (char *)string_table + symtab[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_ABS)
				ft_printf("%017llx %c %s\n", symtab[i].n_value, 'A', (char *)string_table + symtab[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_SECT)
				ft_printf("%017llx %c %s\n", symtab[i].n_value, 'T', (char *)string_table + symtab[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_PBUD)
				ft_printf("%017llx %c %s\n", symtab[i].n_value, 'P', (char *)string_table + symtab[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_INDR)
				ft_printf("%017llx %c %s\n", symtab[i].n_value, 'I', (char *)string_table + symtab[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_EXT))
				ft_printf("%017llx %c %s\n", symtab[i].n_value, 'E', (char *)string_table + symtab[i].n_un.n_strx);
			nlist_64 += 1;
		}
	}
	else
	{
		nlist_64 = (t_nlist_64 *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->symoff);
		string_table = (char *)((char *)mach_header_64 + ((t_symtab_command*)load_command)->stroff);
		while (++i < ((t_symtab_command*)load_command)->nsyms)
		{
			if ((symtab[i].n_type & N_STAB))
			;//		ft_printf("%017llx %c %s\n", symtab[i].n_value, 'S', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_UNDF)
				ft_printf("%-7c %c %s\n", ' ', 'U', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_ABS)
				ft_printf("%07llx %c %s\n", ((t_nlist*)symtab)[i].n_value, 'A', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_SECT)
				ft_printf("%07llx %c %s\n", ((t_nlist*)symtab)[i].n_value, 'T', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_PBUD)
				ft_printf("%07llx %c %s\n", ((t_nlist*)symtab)[i].n_value, 'P', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_TYPE) == N_INDR)
				ft_printf("%07llx %c %s\n", ((t_nlist*)symtab)[i].n_value, 'I', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			else if ((symtab[i].n_type & N_EXT))
				ft_printf("%07llx %c %s\n", ((t_nlist*)symtab)[i].n_value, 'E', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			else
				ft_printf("%-7c %c %s\n", ' ', 'U', (char *)string_table + ((t_nlist*)symtab)[i].n_un.n_strx);
			nlist_64 = (t_nlist_64*)((t_nlist*)nlist_64 + 1);
		}
	}
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
		nlist_64 += 1;
	}
	return (symtab);
}
