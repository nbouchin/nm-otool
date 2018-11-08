/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 14:19:56 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

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

t_section_64	*otool_get_section(t_load_command const *load_command,
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
