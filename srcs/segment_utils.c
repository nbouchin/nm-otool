/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/26 09:13:54 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

t_section_64	*alloc_sectab_64(t_section_64 *sectab, t_metadata *metadata, t_segment_command_64 const *sc_64)
{
	metadata->nsect += sc_64->nsects;
	sectab = (sectab == NULL) ? malloc(sc_64->nsects * sizeof(t_section_64))
		: realloc(sectab, metadata->nsect * sizeof(t_section_64));// TODO : make a nm realloc
	return (sectab);
}

t_section_64	*alloc_sectab(t_mach_header_64 const *mach_header_64, t_section_64 *sectab, t_metadata *metadata, t_segment_command const *sc)
{
	if (mach_header_64->magic == MH_CIGAM)
	{
		metadata->nsect += OSSwapInt32(sc->nsects);
		sectab = (sectab == NULL) ? malloc(OSSwapInt32(sc->nsects) * sizeof(t_section_64))
			: realloc(sectab, metadata->nsect * sizeof(t_section_64));// TODO : make a nm realloc
	}
	else
	{
		metadata->nsect += sc->nsects;
		sectab = (sectab == NULL) ? malloc(sc->nsects * sizeof(t_section_64))
			: realloc(sectab, metadata->nsect * sizeof(t_section_64));// TODO : make a nm realloc
	}
	return (sectab);
}

t_section_64	*get_sectab(t_load_command const *load_command, t_mach_header_64 const *mach_header_64, t_metadata *metadata)
{
	static t_section_64		*sectab = NULL;
	t_section_64		   	*section;
	t_segment_command_64	*sc_64;
	t_segment_command		*sc;

	if (is_64bits(mach_header_64->magic))
	{
		sc_64 = (t_segment_command_64*)(load_command);
		section = (t_section_64*)(sc_64 + 1);
		sectab = alloc_sectab_64(sectab, metadata, sc_64);
	}
	else
	{
		sc = (t_segment_command*)load_command;
		section = (t_section_64*)(sc + 1);
		sectab = alloc_sectab(mach_header_64, sectab, metadata, sc);
	}
	return (sectab);
}

t_section_64	*get_current_section(t_load_command const *load_command, t_mach_header_64 const *mach_header_64)
{
	t_section_64		   	*section;
	t_segment_command_64	*segment_command_64;
	t_segment_command		*segment_command;

	if (is_64bits(mach_header_64->magic))
	{
		segment_command_64 = (t_segment_command_64*)(load_command);
		section = (t_section_64*)(segment_command_64 + 1);
	}
	else
	{
		segment_command = (t_segment_command*)load_command;
		section = (t_section_64*)(segment_command + 1);
	}
	return (section);
}

t_section_64	*get_section(t_load_command const *load_command, t_mach_header_64 const *mach_header_64, t_metadata *metadata)
{
	int            i;
	t_section_64   *sectab;
	t_section_64   *section;

	i = metadata->nsect;
	sectab = get_sectab(load_command, mach_header_64, metadata);
	section = get_current_section(load_command, mach_header_64);
	while (i < (int)metadata->nsect)
	{
		sectab[i] = *section;
		if (is_64bits(mach_header_64->magic))
			section++;
		else
			section = (t_section_64*)((t_section*)section + 1);
		i++;
	}
	return (sectab);
}
