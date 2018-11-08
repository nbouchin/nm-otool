/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 15:43:33 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

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
