/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:49:09 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/18 16:29:49 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		regular_header(t_mach_header_64 *mach_header_64)
{
	static int			pass = 0;
	uint32_t			ncmds;
	t_nlist_64			*symtab;
	t_load_command		*load_command;

	ncmds = 0;
	symtab = NULL;
	load_command = NULL;
	ncmds = mach_header_64->ncmds;
	if (mach_header_64->magic != MH_MAGIC)
	{
		pass = 1;
		load_command = (t_load_command*)(mach_header_64 + 1);
		while (--ncmds)
		{
			if (load_command->cmd == LC_SYMTAB)
			{
				symtab = get_symtab(load_command, mach_header_64);
				print_symtab(load_command, mach_header_64, symtab);
				free (symtab);
			}
			load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
		}
	}
	else if (mach_header_64->magic == MH_MAGIC && pass == 0)
	{
		load_command = (t_load_command*)((t_mach_header*)mach_header_64 + 1);
		while (--ncmds)
		{
			if (load_command->cmd == LC_SYMTAB)
			{
				symtab = get_symtab(load_command, mach_header_64);
				print_symtab(load_command, mach_header_64, symtab);
				free (symtab);
			}
			load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
		}
	}
	return (1);
}
