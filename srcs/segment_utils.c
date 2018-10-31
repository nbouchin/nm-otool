/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/31 17:07:47 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

t_section_64	*sectab_realloc(t_section_64 *sectab, size_t new_size,
		uint32_t old_size)
{
	t_section_64	*swap;

	swap = (t_section_64*)ft_memalloc(new_size);
	swap = ft_memcpy(swap, sectab, old_size * sizeof(t_section_64));
	free(sectab);
	return (swap);
}

t_section_64	*alloc_sectab_64(t_section_64 *sectab, t_metadata *metadata,
		t_segment_command_64 const *sc_64)
{
	int32_t	old_size;

	old_size = metadata->nsect;
	metadata->nsect += sc_64->nsects;
	sectab = (sectab == NULL) ? ft_memalloc(sc_64->nsects * sizeof(t_section_64))
	: sectab_realloc(sectab, metadata->nsect * sizeof(t_section_64), old_size);
	return (sectab);
}

t_section_64	*alloc_sectab(t_mach_header_64 const *mach_header_64,
	t_section_64 *sectab, t_metadata *mdata, t_segment_command const *sc)
{
	int32_t	old_size;

	old_size = mdata->nsect;
	if (mach_header_64->magic == MH_CIGAM)
	{
		mdata->nsect += ft_OSSwapInt32(sc->nsects);
		sectab = (sectab == NULL)
		? ft_memalloc(ft_OSSwapInt32(sc->nsects) * sizeof(t_section_64))
		: sectab_realloc(sectab, mdata->nsect * sizeof(t_section_64), old_size);
	}
	else
	{
		mdata->nsect += sc->nsects;
		sectab = (sectab == NULL)
		? ft_memalloc(sc->nsects * sizeof(t_section_64))
		: sectab_realloc(sectab, mdata->nsect * sizeof(t_section_64), old_size);
	}
	return (sectab);
}

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
			section++;
		else
			section = (t_section_64*)((t_section*)section + 1);
		i++;
	}
	return (sectab);
}
