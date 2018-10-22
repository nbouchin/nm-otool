/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:49:09 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/22 14:25:57 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		process_header(t_mach_header_64 *mach_header_64, uint32_t magic)
{
	static int			pass = 0;
	uint32_t			ncmds;
	t_load_command		*load_command;
	t_metadata			*metadata;

	ncmds = 0;
	load_command = NULL;
	ncmds = mach_header_64->ncmds;
	metadata = (t_metadata*)malloc(sizeof(t_metadata));
	if (magic != MH_MAGIC)//is_64bits(magic))
	{
		pass = 1;
		load_command = (t_load_command*)(mach_header_64 + 1);
		while (--ncmds)
		{
			if (load_command->cmd == LC_SEGMENT_64)
			{
				metadata->sectab = get_section(load_command, mach_header_64);
			}
			else if (load_command->cmd == LC_SYMTAB)
			{
				metadata->symtab = get_symtab(load_command, mach_header_64);
				print_symtab(load_command, mach_header_64, metadata);
				free (metadata->symtab);
				free (metadata->sectab);
			}
			load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
		}
	}
	else if (magic == MH_MAGIC && pass == 0)//is_32bits(magic) && pass == 0)
	{
		load_command = (t_load_command*)((t_mach_header*)mach_header_64 + 1);
		while (--ncmds)
		{
			if (load_command->cmd == LC_SYMTAB)
			{
				metadata->symtab = get_symtab(load_command, mach_header_64);
				print_symtab(load_command, mach_header_64, metadata);
				free (metadata->symtab);
			}
			load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
		}
	}
	free(metadata);
	return (1);
}
