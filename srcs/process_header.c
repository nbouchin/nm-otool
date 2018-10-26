/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:49:09 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/26 11:05:46 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

t_metadata	*get_metadata_64(t_mach_header_64 const *mach_header_64)
{
	uint32_t			ncmds;
	t_load_command		*lcommand;
	t_metadata			*mdata;

	ncmds = mach_header_64->ncmds;
	mdata = (t_metadata*)malloc(sizeof(t_metadata));
	lcommand = (t_load_command*)(mach_header_64 + 1);
	while (--ncmds)
	{
		if (lcommand->cmd == LC_SEGMENT_64)
			mdata->sectab = get_section(lcommand, mach_header_64, mdata);
		else if (lcommand->cmd == LC_SYMTAB)
		{
			mdata->symtab = get_symtab(lcommand, mach_header_64);
			print_symtab(lcommand, mach_header_64, mdata);
			(mdata->symtab) ? free(mdata->symtab) : 0;
		}
		lcommand = (t_load_command*)((char*)lcommand + lcommand->cmdsize);
	}
	return (mdata);
}

t_metadata	*get_big_metadata_32(t_mach_header_64 const *mach_header_64)
{
	uint32_t			ncmds;
	t_load_command		*lcommand;
	t_metadata			*metadata;

	ncmds = OSSwapInt32(mach_header_64->ncmds);
	metadata = (t_metadata*)malloc(sizeof(t_metadata));
	lcommand = (t_load_command*)((t_mach_header*)mach_header_64 + 1);
	while (--ncmds)
	{
		if (OSSwapInt32(lcommand->cmd) == LC_SEGMENT)
			metadata->sectab = get_section(lcommand, mach_header_64, metadata);
		else if (OSSwapInt32(lcommand->cmd) == LC_SYMTAB)
		{
			metadata->symtab = get_big_symtab(lcommand, mach_header_64);
			print_big_symtab(lcommand, mach_header_64, metadata);
			(metadata->symtab) ? free(metadata->symtab) : 0;
		}
		lcommand = (t_load_command*)((char*)lcommand
				+ OSSwapInt32(lcommand->cmdsize));
	}
	return (metadata);
}

t_metadata	*get_metadata_32(t_mach_header_64 const *mach_header_64)
{
	uint32_t			ncmds;
	t_load_command		*lcommand;
	t_metadata			*mdata;

	ncmds = mach_header_64->ncmds;
	mdata = (t_metadata*)malloc(sizeof(t_metadata));
	lcommand = (t_load_command*)((t_mach_header*)mach_header_64 + 1);
	while (--ncmds)
	{
		if (lcommand->cmd == LC_SEGMENT)
			mdata->sectab = get_section(lcommand, mach_header_64, mdata);
		else if (lcommand->cmd == LC_SYMTAB)
		{
			mdata->symtab = get_symtab(lcommand, mach_header_64);
			print_symtab(lcommand, mach_header_64, mdata);
			(mdata->symtab) ? free(mdata->symtab) : 0;
		}
		lcommand = (t_load_command*)((char*)lcommand + lcommand->cmdsize);
	}
	return (mdata);
}

int		process_header(t_mach_header_64 const *mach_header_64,
		uint32_t const magic)
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
