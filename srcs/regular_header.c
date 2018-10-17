/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:49:09 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/17 17:03:08 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		regular_header(t_mach_header *mach_header)
{
	uint32_t		ncmds;
	t_nlist			*symtab;
	t_load_command	*load_command;

	ncmds = mach_header->ncmds + 1;
	load_command = (t_load_command*)(mach_header + 1);
	while (--ncmds)
	{
		if (load_command->cmd == LC_SYMTAB)
		{
			symtab = get_symtab(load_command, mach_header);
			print_symtab(load_command, mach_header, symtab);
			free (symtab);
		}
		load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
	}
	return (1);
}

