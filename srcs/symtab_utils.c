/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:55:50 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/17 17:04:08 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

void		print_symtab(t_load_command *load_command, t_mach_header *mach_header, t_nlist *symtab)
{
	uint32_t	i;
	t_nlist		*nlist;
	char		*string_table;

	i = -1;
	nlist = (t_nlist *)((char *)mach_header + ((t_symtab_command*)load_command)->symoff);
	string_table = (char *)((char *)mach_header + ((t_symtab_command*)load_command)->stroff);
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		if ((symtab[i].n_type & N_STAB))
			;//		printf("%017llx %c %s\n", symtab[i].n_value, 'S', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_UNDF)
			printf("%-17c %c %s\n", ' ', 'U', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_ABS)
			printf("%017llx %c %s\n", symtab[i].n_value, 'A', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_SECT)
			printf("%017llx %c %s\n", symtab[i].n_value, 'T', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_PBUD)
			printf("%017llx %c %s\n", symtab[i].n_value, 'P', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_INDR)
			printf("%017llx %c %s\n", symtab[i].n_value, 'I', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_EXT))
			printf("%017llx %c %s\n", symtab[i].n_value, 'E', (char *)string_table + symtab[i].n_un.n_strx);
		nlist += 1;
	}
}

t_nlist		*get_symtab(t_load_command *load_command, t_mach_header *mach_header)
{
	uint32_t			i;
	t_nlist				*nlist;
	t_nlist				*symtab;

	i = -1;
	nlist = (t_nlist *)((char *)mach_header + ((t_symtab_command*)load_command)->symoff);
	symtab = malloc(((t_symtab_command*)load_command)->nsyms * sizeof(t_nlist));
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		symtab[i] = *nlist;
		nlist += 1;
	}
	return (symtab);
}
