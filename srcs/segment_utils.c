/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 17:00:08 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/19 17:52:50 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"


t_section_64	*get_section(t_load_command *load_command, t_mach_header_64 *mach_header_64)
{
	unsigned long			i;
	unsigned long	 		nsects;
	t_section_64			*sectab;
	t_section_64		   	*section;
	t_segment_command_64	*segment_command;
 
	i = 0;
	segment_command = (t_segment_command_64*)(load_command);// Casting command into segment_command.
	nsects = segment_command->nsects;	
	section = (t_section_64*)(segment_command + 1);
	sectab = malloc(nsects * sizeof(t_section_64));
	while (nsects)
	{
		sectab[i] = *section;
		if (mach_header_64->magic != MH_MAGIC)
			section++;
		else
			section = (t_section_64*)((t_section*)section + 1);
		nsects--;
		i++;
	}
	i = 0;
	nsects = segment_command->nsects;	
	while (i != nsects)
	{
		printf("%s\n", sectab[i].sectname);
		i++;
	}
	return sectab;
}
