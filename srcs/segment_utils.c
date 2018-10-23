/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/23 14:58:31 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

t_section_64	*get_sectab(t_load_command *load_command, t_mach_header_64 *mach_header_64, t_metadata *metadata)
{
	static t_section_64		*sectab = NULL;
	t_section_64		   	*section;
	t_segment_command_64	*segment_command_64;
	t_segment_command		*segment_command;

	if (is_64bits(mach_header_64->magic))
	{
		segment_command_64 = (t_segment_command_64*)(load_command);
		metadata->nsect += segment_command_64->nsects;
		section = (t_section_64*)(segment_command_64 + 1);
		if (sectab == NULL)
			sectab = malloc(segment_command_64->nsects * sizeof(t_section_64));
		else
			sectab = realloc(sectab, metadata->nsect * sizeof(t_section_64));// TODO : make a nm realloc
	}
	else
	{
		segment_command = (t_segment_command*)load_command;
		metadata->nsect += segment_command->nsects;
		section = (t_section_64*)(segment_command + 1);
		if (sectab == NULL)
			sectab = malloc(segment_command->nsects * sizeof(t_section_64));
		else
			sectab = realloc(sectab, metadata->nsect * sizeof(t_section_64));// TODO : make a nm realloc
	}
	return (sectab);
}

t_section_64	*get_section(t_load_command *load_command, t_mach_header_64 *mach_header_64, t_metadata *metadata)
{
	int						i;
	static t_section_64		*sectab = NULL;
	t_section_64		   	*section;
	t_segment_command_64	*segment_command_64;
	t_segment_command		*segment_command;

	i = metadata->nsect;
	if (is_64bits(mach_header_64->magic))
	{
		segment_command_64 = (t_segment_command_64*)(load_command);
		metadata->nsect += segment_command_64->nsects;
		section = (t_section_64*)(segment_command_64 + 1);
		if (sectab == NULL)
			sectab = malloc(segment_command_64->nsects * sizeof(t_section_64));
		else
			sectab = realloc(sectab, metadata->nsect * sizeof(t_section_64));// TODO : make a nm realloc
	}
	else
	{
		segment_command = (t_segment_command*)load_command;
		metadata->nsect += segment_command->nsects;
		section = (t_section_64*)(segment_command + 1);
		if (sectab == NULL)
			sectab = malloc(segment_command->nsects * sizeof(t_section_64));
		else
			sectab = realloc(sectab, metadata->nsect * sizeof(t_section_64));// TODO : make a nm realloc
	}
	while (i < (int)metadata->nsect)
	{
		sectab[i] = *section;
		if (is_64bits(mach_header_64->magic))
			section++;
		else
			section = (t_section_64*)((t_section*)section + 1);
		i++;
	}
	return sectab;
}
