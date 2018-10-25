/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:49:09 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/25 15:06:41 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

t_metadata	*get_metadata_64(t_mach_header_64 *mach_header_64)
{
	uint32_t			ncmds;
	t_load_command		*load_command;
	t_metadata			*metadata;

	ncmds = mach_header_64->ncmds;
	metadata = (t_metadata*)malloc(sizeof(t_metadata));
	load_command = (t_load_command*)(mach_header_64 + 1);
	while (--ncmds)
	{
		if (load_command->cmd == LC_SEGMENT_64)
			metadata->sectab = get_section(load_command, mach_header_64, metadata);
		else if (load_command->cmd == LC_SYMTAB)
		{
			metadata->symtab = get_symtab(load_command, mach_header_64);
			print_symtab(load_command, mach_header_64, metadata);
			(metadata->symtab) ? free(metadata->symtab) : 0;
		}
		load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
	}
	return metadata;
}

t_metadata	*get_big_metadata_32(t_mach_header_64 *mach_header_64)
{
	uint32_t			ncmds;
	t_load_command		*load_command;
	t_metadata			*metadata;

	ncmds = OSSwapInt32(mach_header_64->ncmds);
	metadata = (t_metadata*)malloc(sizeof(t_metadata));
	load_command = (t_load_command*)((t_mach_header*)mach_header_64 + 1);
	while (--ncmds)
	{
		if (OSSwapInt32(load_command->cmd) == LC_SEGMENT)
			metadata->sectab = get_section(load_command, mach_header_64, metadata);
		else if (OSSwapInt32(load_command->cmd) == LC_SYMTAB)
		{
			metadata->symtab = get_big_symtab(load_command, mach_header_64);
			print_big_symtab(load_command, mach_header_64, metadata);
			(metadata->symtab) ? free(metadata->symtab) : 0;
		}
		load_command = (t_load_command*)((char*)load_command + OSSwapInt32(load_command->cmdsize));
	}
	return (metadata);
}

t_metadata	*get_metadata_32(t_mach_header_64 *mach_header_64)
{
	uint32_t			ncmds;
	t_load_command		*load_command;
	t_metadata			*metadata;

	ncmds = mach_header_64->ncmds;
	metadata = (t_metadata*)malloc(sizeof(t_metadata));
	load_command = (t_load_command*)((t_mach_header*)mach_header_64 + 1);
	while (--ncmds)
	{
		if (load_command->cmd == LC_SEGMENT)
			metadata->sectab = get_section(load_command, mach_header_64, metadata);
		else if (load_command->cmd == LC_SYMTAB)
		{
			metadata->symtab = get_symtab(load_command, mach_header_64);
			print_symtab(load_command, mach_header_64, metadata);
			(metadata->symtab) ? free(metadata->symtab) : 0;
		}
		load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
	}
	return (metadata);
}

int		process_header(t_mach_header_64 *mach_header_64, uint32_t magic)
{
	static int			pass = 0;
	t_metadata			*metadata;

	metadata = NULL;
	if (is_64bits(magic))
	{
		pass = 1;
		metadata = get_metadata_64(mach_header_64);
	}
	else if (is_32bits(magic) && pass == 0)
	{
		if (mach_header_64->magic == MH_CIGAM)
			metadata = get_big_metadata_32(mach_header_64);
		else
			metadata = get_metadata_32(mach_header_64);
	}
	free(metadata);
	return (1);
}
