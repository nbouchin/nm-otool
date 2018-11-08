/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 13:09:10 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

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
	sectab = (sectab == NULL)
	? ft_memalloc(sc_64->nsects * sizeof(t_section_64))
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
		mdata->nsect += swi(sc->nsects);
		sectab = (sectab == NULL)
		? ft_memalloc(swi(sc->nsects) * sizeof(t_section_64))
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

void			print_section(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	uint64_t	i;
	char		*section_string;
	char		*address;

	i = 0;
	address = (char*)section->addr;
	section_string = (char *)mach_header_64 + section->offset;
	while (i < section->size)
	{
		if (i == 0)
			ft_putendl("");
		if (i % 16 == 0)
		{
			if (i > 0)
				ft_putendl("");
			ft_printf("%016lx\t", address);
		}
		ft_printf("%02x ", (uint8_t)(*section_string));
		address++;
		section_string++;
		i++;
	}
	ft_putendl("");
}

void			print_section_32(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	uint32_t	i;
	char		*section_string;
	uint32_t	address;

	i = 0;
	address = ((t_section*)section)->addr;
	section_string = (char *)mach_header_64 + ((t_section*)section)->offset;
	while (i < ((t_section*)section)->size)
	{
		if (i == 0)
			ft_putendl("");
		if (i % 16 == 0)
		{
			if (i > 0)
				ft_putendl("");
			ft_printf("%08lx\t", address);
		}
		ft_printf("%02x ", (uint8_t)(*section_string));
		address++;
		section_string++;
		i++;
	}
	ft_putendl("");
}

void			print_big_section_32(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	uint32_t	i;
	char		*st;
	uint32_t	address;

	i = 0;
	address = swi(((t_section*)section)->addr);
	st = (char *)mach_header_64 + swi(((t_section*)section)->offset);
	while (i < swi(((t_section*)section)->size))
	{
		if (i == 0)
			ft_putendl("");
		if (i % 4 == 0 && i > 0)
			ft_putchar(' ');
		if (i % 16 == 0)
		{
			if (i > 0)
				ft_putendl("");
			ft_printf("%08lx\t", address);
		}
		ft_printf("%02x", (uint8_t)(*st));
		address++;
		st++;
		i++;
	}
	ft_putendl(" ");
}

void			process_section_32(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	if (mach_header_64->magic == MH_CIGAM)
		print_big_section_32(mach_header_64, section);
	else
		print_section_32(mach_header_64, section);
}

void			process_section(t_mach_header_64 const *mach_header_64,
		t_section_64 *section)
{
	ft_printf("Contents of (__TEXT,__text) section");
	if (is_64bits(mach_header_64->magic))
		print_section(mach_header_64, section);
	else
		process_section_32(mach_header_64, section);
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
		if (!ft_strcmp(section->segname, "__TEXT")
				&& !ft_strcmp(section->sectname, "__text"))
			process_section(mach_header_64, section);
		if (is_64bits(mach_header_64->magic))
			section++;
		else
			section = (t_section_64*)((t_section*)section + 1);
		i++;
	}
	return (NULL);
}
