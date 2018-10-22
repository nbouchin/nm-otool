/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/22 14:31:31 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"


t_section_64	*get_section(t_load_command *load_command, t_mach_header_64 *mach_header_64)
{
	static int				i;
	static t_section_64		*sectab = NULL;
	t_section_64		   	*section;
	t_segment_command_64	*segment_command;
 
	i = -1;
	segment_command = (t_segment_command_64*)(load_command);
	section = (t_section_64*)(segment_command + 1);

	if (sectab == NULL)
		sectab = malloc(segment_command->nsects * sizeof(t_section_64));
	else
		sectab = realloc(sectab, (segment_command->nsects + i) * sizeof(t_section_64));
	while (++i < (int)segment_command->nsects)
	{
		sectab[i] = *section;
		if (mach_header_64->magic != MH_MAGIC)
			section++;
		else
			section = (t_section_64*)((t_section*)section + 1);
	}
	return sectab;
}
