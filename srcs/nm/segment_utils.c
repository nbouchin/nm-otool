/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 13:28:29 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

t_section_64	*get_sectab(t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64, t_metadata *metadata)
{
	static t_section_64		*sectab = NULL;
	t_segment_command_64	*sc_64;
	t_segment_command		*sc;

	if (is_64bits(mach_header_64->magic))
	{
		sc_64 = (t_segment_command_64*)(load_command);
		sectab = alloc_sectab_64(sectab, metadata, sc_64);
	}
	else
	{
		sc = (t_segment_command*)load_command;
		sectab = alloc_sectab(mach_header_64, sectab, metadata, sc);
	}
	return (sectab);
}

t_section_64	*get_current_section(t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64)
{
	t_section_64			*section;
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

t_section_64	*get_section(t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64, t_metadata *metadata)
{
	int				i;
	t_section_64	*sectab;
	t_section_64	*section;

	i = metadata->nsect;
	sectab = get_sectab(load_command, mach_header_64, metadata);
	section = get_current_section(load_command, mach_header_64);
	while (i < metadata->nsect)
	{
		sectab[i] = *section;
		if (is_64bits(mach_header_64->magic))
		{
			if (is_out((char *)(section + 1)))
				return (NULL);
			section++;
		}
		else
		{
			if (is_out((char *)((t_section*)section + 1)))
				return (NULL);
			section = (t_section_64*)((t_section*)section + 1);
		}
		i++;
	}
	return (sectab);
}
